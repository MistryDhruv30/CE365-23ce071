#include <iostream>   
#include <string>
using namespace std;

int main() {
    int nSymbols;
    cout << "Number of input symbols : ";
    cin >> nSymbols;

    char symbols[nSymbols];
    cout << "Input symbols : ";
    for (int i = 0; i < nSymbols; i++) {
        cin >> symbols[i];
    }

    int nStates;
    cout << "Enter number of states : ";
    cin >> nStates;

    int startState;
    cout << "Initial state : ";
    cin >> startState;

    int nAccept;
    cout << "Number of accepting states : ";
    cin >> nAccept;

    int acceptStates[nAccept];
    cout << "Accepting states : ";
    for (int i = 0; i < nAccept; i++) {
        cin >> acceptStates[i];
    }

    int transition[nStates + 1][nSymbols];  

    cout << "Transition table :" << endl;
    for (int i = 1; i <= nStates; i++) {
        for (int j = 0; j < nSymbols; j++) {
            cout << i << " to " << symbols[j] << " -> ";
            cin >> transition[i][j];
        }
    }

    string input;
    cout << "Input string : ";
    cin >> input;

    int currentState = startState;

    for (int i = 0; i < input.length(); i++) {
        bool found = false;

        for (int j = 0; j < nSymbols; j++) {
            if (input[i] == symbols[j]) {
                currentState = transition[currentState][j];
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Invalid String";
            return 0;
        }
    }

    for (int i = 0; i < nAccept; i++) {
        if (currentState == acceptStates[i]) {
            cout << "Valid String";
            return 0;
        }
    }

    cout << "Invalid String";
    return 0;
}
