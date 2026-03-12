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
 int main(){
    
 }