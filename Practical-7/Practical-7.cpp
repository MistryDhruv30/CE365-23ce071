#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Using the UTF-8 literal for Epsilon
const string EPS = "ε";

// Helper to keep elements unique while preserving "Discovery Order"
void addToSet(vector<string>& vec, const string& val) {
    if (find(vec.begin(), vec.end(), val) == vec.end()) {
        vec.push_back(val);
    }
}

// Adds one set into another while maintaining order and skipping Epsilon if needed
void addSetToSet(vector<string>& dest, const vector<string>& src, bool excludeEpsilon = false) {
    for (const auto& s : src) {
        if (excludeEpsilon && s == EPS) continue;
        addToSet(dest, s);
    }
}

bool isTerminal(string s) {
    if (s == EPS || s == "$") return false;
    return !isupper(s[0]);
}

vector<string> split(const string &s, char delim) {
    vector<string> result;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        size_t first = item.find_first_not_of(" \t\r\n");
        if (string::npos != first) {
            size_t last = item.find_last_not_of(" \t\r\n");
            result.push_back(item.substr(first, (last - first + 1)));
        }
    }
    return result;
}

int main() {
    // FIX FOR "╬╡": Programmatically switch terminal to UTF-8 mode
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif

    map<string, vector<vector<string>>> grammar;
    vector<string> nonTerminals;
    
    ifstream file("cfg.txt");
    if (!file.is_open()) {
        cerr << "Error: Please create 'cfg.txt' with the grammar first!" << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        size_t pos = line.find("->");
        string sep = "->";
        if (pos == string::npos) { pos = line.find("→"); sep = "→"; }
        if (pos != string::npos) {
            string lhs = line.substr(0, pos);
            lhs.erase(0, lhs.find_first_not_of(" "));
            lhs.erase(lhs.find_last_not_of(" ") + 1);
            if (find(nonTerminals.begin(), nonTerminals.end(), lhs) == nonTerminals.end())
                nonTerminals.push_back(lhs);
            string rhsPart = line.substr(pos + sep.length());
            vector<string> alts = split(rhsPart, '|');
            for (string a : alts) grammar[lhs].push_back(split(a, ' '));
        }
    }
    file.close();

    map<string, vector<string>> first, follow;

    // 1. Compute FIRST Sets
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto& nt : nonTerminals) {
            size_t oldSize = first[nt].size();
            for (auto& prod : grammar[nt]) {
                bool allEps = true;
                for (auto& sym : prod) {
                    if (sym == EPS) {
                        addToSet(first[nt], EPS);
                        break;
                    } else if (isTerminal(sym)) {
                        addToSet(first[nt], sym);
                        allEps = false;
                        break;
                    } else {
                        addSetToSet(first[nt], first[sym], true);
                        bool ntHasEps = false;
                        for(auto& s : first[sym]) if(s == EPS) ntHasEps = true;
                        if (!ntHasEps) { allEps = false; break; }
                    }
                }
                if (allEps) addToSet(first[nt], EPS);
            }
            if (first[nt].size() > oldSize) changed = true;
        }
    }

    // 2. Compute FOLLOW Sets
    addToSet(follow[nonTerminals[0]], "$");
    changed = true;
    while (changed) {
        changed = false;
        for (auto& head : nonTerminals) {
            for (auto& prod : grammar[head]) {
                for (size_t i = 0; i < prod.size(); ++i) {
                    string B = prod[i];
                    if (isTerminal(B) || B == EPS) continue;
                    size_t oldSize = follow[B].size();
                    bool canDeriveEps = true;
                    for (size_t j = i + 1; j < prod.size(); ++j) {
                        string next = prod[j];
                        if (isTerminal(next)) {
                            addToSet(follow[B], next);
                            canDeriveEps = false;
                            break;
                        } else {
                            addSetToSet(follow[B], first[next], true);
                            bool ntHasEps = false;
                            for(auto& s : first[next]) if(s == EPS) ntHasEps = true;
                            if (!ntHasEps) { canDeriveEps = false; break; }
                        }
                    }
                    if (canDeriveEps) addSetToSet(follow[B], follow[head]);
                    if (follow[B].size() > oldSize) changed = true;
                }
            }
        }
    }

    // 3. Print Final Output
    for (auto& nt : nonTerminals) {
        cout << "First(" << nt << ") = {";
        for (size_t i = 0; i < first[nt].size(); ++i)
            cout << first[nt][i] << (i == first[nt].size() - 1 ? "" : ", ");
        cout << "}" << endl;
    }

    for (auto& nt : nonTerminals) {
        cout << "Follow(" << nt << ") = {";
        vector<string> items = follow[nt];
        // Move $ to the end and ensure ) comes before $ to match expected output
        sort(items.begin(), items.end(), [](string a, string b){
            if (a == "$") return false;
            if (b == "$") return true;
            return a < b;
        });
        for (size_t i = 0; i < items.size(); ++i)
            cout << items[i] << (i == items.size() - 1 ? "" : ", ");
        cout << "}" << endl;
    }

    return 0;
}