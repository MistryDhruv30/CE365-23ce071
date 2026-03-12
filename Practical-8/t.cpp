#include <iostream>
#include <cstring>
using namespace std;

#define NT 3
#define T 5

char nonTerminals[NT] = {'S','A','B'};
char terminals[T] = {'a','b','(',')','$'};

char table[NT][T][20];
bool isLL1 = true;

/* return index of non-terminal */
int ntIndex(char ch){
    for(int i=0;i<NT;i++)
        if(nonTerminals[i]==ch) return i;
    return -1;
}

/* return index of terminal */
int tIndex(char ch){
    for(int i=0;i<T;i++)
        if(terminals[i]==ch) return i;
    return -1;
}

/* construct predictive parsing table */
void constructTable(){

    // initialize table with empty strings
    for(int i=0;i<NT;i++)
        for(int j=0;j<T;j++)
            table[i][j][0] = '\0';

    // S → AB
    strcpy(table[0][0], "AB"); // S,a
    strcpy(table[0][1], "AB"); // S,b

    // A → aA
    strcpy(table[1][0], "aA"); // A,a

    // A → ε
    strcpy(table[1][1], "e");  // A,b
    strcpy(table[1][4], "e");  // A,$

    // B → bB
    strcpy(table[2][1], "bB"); // B,b

    // B → ε
    strcpy(table[2][4], "e");  // B,$
}

/* print parsing table */
void printTable(){
    cout<<"\nPredictive Parsing Table:\n\n";
    cout<<"     ";
    for(int i=0;i<T;i++)
        cout<<terminals[i]<<"     ";
    cout<<"\n";

    for(int i=0;i<NT;i++){
        cout<<nonTerminals[i]<<"   ";
        for(int j=0;j<T;j++){
            if(strlen(table[i][j])==0)
                cout<<"-     ";
            else
                cout<<table[i][j]<<"     ";
        }
        cout<<"\n";
    }
}

/* validate string using LL(1) parsing */
void parseString(char input[]){

    char stack[50];
    int top = -1;

    stack[++top] = '$';
    stack[++top] = 'S';

    int i = 0;

    while(top >= 0){

        char topSymbol = stack[top];
        char current = input[i];

        if(topSymbol == current){
            top--;
            i++;
        }
        else if(ntIndex(topSymbol) != -1){

            int row = ntIndex(topSymbol);
            int col = tIndex(current);

            if(col == -1 || strlen(table[row][col]) == 0){
                cout<<"Invalid string\n";
                return;
            }

            top--;

            if(table[row][col][0] != 'e'){
                for(int k=strlen(table[row][col])-1;k>=0;k--)
                    stack[++top] = table[row][col][k];
            }
        }
        else{
            cout<<"Invalid string\n";
            return;
        }
    }

    if(input[i] == '\0')
        cout<<"Valid string\n";
    else
        cout<<"Invalid string\n";
}

int main(){

    constructTable();
    printTable();

    if(isLL1)
        cout<<"\nGrammar is LL(1)\n";
    else{
        cout<<"\nGrammar is NOT LL(1)\n";
        return 0;
    }

    char input[50];
    cout<<"\nEnter string: ";
    cin>>input;

    strcat(input,"$");

    parseString(input);

    return 0;
}