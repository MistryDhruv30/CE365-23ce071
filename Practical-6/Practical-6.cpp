#include <iostream>
#include <string>
using namespace std;

string s;
int i = 0;

bool S();
bool L_dash();
bool L() {
    if (S()) {
        return L_dash();
    }
    return false;
} 
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
    cout << "Enter string to validate: ";
    cin >> s;

    if (S() && i == s.length()) {
        cout << "Valid string";
    } else {
        cout << "ERROR:Invalid string !";
    }

    return 0;
}
