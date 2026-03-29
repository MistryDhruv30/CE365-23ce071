#include <iostream>
#include <string>
using namespace std;

string s;
int i = 0;

bool S();
bool L();
bool L_dash();

bool S() {
    if (i >= s.length()) return false;

    if (s[i] == 'a') {
        i++;
        return true;
    }
    else if (s[i] == '(') {
        i++; 
        if (L()) {
            if (i < s.length() && s[i] == ')') {
                i++; 
                return true;
            }
        }
        return false;
    }
    return false;
}

bool L() {
    if (S()) {
        return L_dash();
    }
    return false;
}

bool L_dash() {
    if (i < s.length() && s[i] == ',') {
        i++; 
        if (S()) {
            return L_dash();
        }
        return false;
    }
    return true; 
}

int main() {
    while (true) {
        cout << "\nEnter string : ";
        cin >> s;

        i = 0;  // reset pointer

        // STRICT: Start from S
        if (S() && i == s.length()) {
            cout << "Valid string";
        } else {
            cout << "Invalid string";
        }
    }

    return 0;
}