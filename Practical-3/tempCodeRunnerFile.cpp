#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

char keywords[10][10] = {
    "int","float","char","void","long","return","struct","if","else","for"
};

char symbolTable[100][30];
int symCount = 0;

int find_keyword(char word[]) {
    for (int i = 0; i < 10; i++)
        {
            if (strcmp(keywords[i], word) == 0)
            return 1;
        }
    return 0;
}

int find_identifierPresent(char id[]) {
    for (int i = 0; i < symCount; i++)
        {
            if (strcmp(symbolTable[i], id) == 0)
            return 1;
        }
    return 0;
}

int find_validIdentifier(char id[]) {
    if (!isalpha(id[0]) && id[0] != '_')
        return 0;

    for (int i = 1; id[i] != '\0'; i++)
        {
            if (!isalnum(id[i]) && id[i] != '_')
            return 0;
        }

    return 1;
}

int main() {
    ifstream file("file.c");
    char ch, word[30];
    int i = 0, line = 1;
    int in_block_comment = 0;

    cout << "\nTOKENS\n";

    while (file.get(ch)) {

        if (ch == '\n')
        {
            line++;
        }

        if (ch == '/') {
            char next = file.peek();
            if (next == '/') {
                while (file.get(ch) && ch != '\n');
                line++;
                continue;
            }
            if (next == '*') {
                file.get();
                 in_block_comment = 1;
                while (file.get(ch)) {
                    if (ch == '\n') line++;
                    if (ch == '*' && file.peek() == '/') {
                        file.get();
                         in_block_comment= 0;
                        break;
                    }
                }
                continue;
            }
        }

        if ( in_block_comment)
        {
            continue;
        }

        if (isalpha(ch) || ch == '_') {
            i = 0;
            word[i++] = ch;
            while (file.get(ch) && (isalnum(ch) || ch == '_'))
                word[i++] = ch;
            word[i] = '\0';

            if (find_keyword(word))
                cout << "Keyword: " << word << endl;
            else {
                cout << "Identifier: " << word << endl;
                if (!find_identifierPresent(word))
                    strcpy(symbolTable[symCount++], word);
            }
            file.unget();
        }

        // Number constant or invalid lexeme
        else if (isdigit(ch)) {
            i = 0;
            word[i++] = ch;
            int invalid = 0;
            while (file.get(ch) && (isalnum(ch) || ch == '.')) {
                if (isalpha(ch)) invalid = 1;
                word[i++] = ch;
            }
            word[i] = '\0';

            if (invalid)
                cout << "ERROR: LEXICAL ERROR Line " << line << " : " << word << endl;
            else
                cout << "Constant: " << word << endl;

            file.unget();
        }

        // Operators
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=') {
            cout << "Operator: " << ch << endl;
        }

        // Punctuation
        else if (ch == '(' || ch == ')' || ch == '{' || ch == '}' ||
                 ch == ';' || ch == ',' ) {
            cout << "Punctuation: " << ch << endl;
        }
    }

    cout << "\nSYMBOL TABLE ENTRIES\n";
    for (int i = 0; i < symCount; i++)
        cout << i + 1 << ") " << symbolTable[i] << endl;

    file.close();
    return 0;
}
