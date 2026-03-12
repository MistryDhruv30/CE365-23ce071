#include <iostream>
using namespace std;

#define NT 5
#define MAX 10

char nonTerminals[NT] = {'S','A','B','C','D'};

char FIRST[NT][MAX];
char FOLLOW[NT][MAX];
int firstCount[NT] = {0};
int followCount[NT] = {0};

int indexOf(char nt) {
    for(int i = 0; i < NT; i++)
        if(nonTerminals[i] == nt)
            return i;
    return -1;
}

bool exists(char set[], int size, char ch) {
    for(int i = 0; i < size; i++)
        if(set[i] == ch)
            return true;
    return false;
}

/* add element to set */
void add(char set[], int &size, char ch) {
    if(!exists(set, size, ch))
        set[size++] = ch;
}

void computeFIRST() {

    add(FIRST[indexOf('A')], firstCount[indexOf('A')], 'a');
    add(FIRST[indexOf('A')], firstCount[indexOf('A')], 'e'); // ε

    add(FIRST[indexOf('B')], firstCount[indexOf('B')], 'b');
    add(FIRST[indexOf('B')], firstCount[indexOf('B')], 'e');

    add(FIRST[indexOf('C')], firstCount[indexOf('C')], '(');
    add(FIRST[indexOf('C')], firstCount[indexOf('C')], 'c');

    add(FIRST[indexOf('D')], firstCount[indexOf('D')], 'a');
    add(FIRST[indexOf('D')], firstCount[indexOf('D')], '(');
    add(FIRST[indexOf('D')], firstCount[indexOf('D')], 'c');

    add(FIRST[indexOf('S')], firstCount[indexOf('S')], 'a');
    add(FIRST[indexOf('S')], firstCount[indexOf('S')], 'b');
    add(FIRST[indexOf('S')], firstCount[indexOf('S')], '(');
    add(FIRST[indexOf('S')], firstCount[indexOf('S')], 'c');
}

void computeFOLLOW() {

    add(FOLLOW[indexOf('S')], followCount[indexOf('S')], ')');
    add(FOLLOW[indexOf('S')], followCount[indexOf('S')], '$');

    add(FOLLOW[indexOf('A')], followCount[indexOf('A')], 'b');
    add(FOLLOW[indexOf('A')], followCount[indexOf('A')], '(');
    add(FOLLOW[indexOf('A')], followCount[indexOf('A')], 'c');

    add(FOLLOW[indexOf('B')], followCount[indexOf('B')], '(');
    add(FOLLOW[indexOf('B')], followCount[indexOf('B')], 'c');

    add(FOLLOW[indexOf('C')], followCount[indexOf('C')], ')');
    add(FOLLOW[indexOf('C')], followCount[indexOf('C')], '$');

    add(FOLLOW[indexOf('D')], followCount[indexOf('D')], ')');
    add(FOLLOW[indexOf('D')], followCount[indexOf('D')], '$');
}

void printSet(const char *name, char set[], int size) {
    cout << name << " = { ";
    for(int i = 0; i < size; i++) {
        if(set[i] == 'e')
            cout << "ε";
        else
            cout << set[i];
        if(i < size - 1) cout << ", ";
    }
    cout << " }" << endl;
}

int main() {

    computeFIRST();
    computeFOLLOW();

    cout << "FIRST Sets:" << endl;
    printSet("First(S)", FIRST[0], firstCount[0]);
    printSet("First(A)", FIRST[1], firstCount[1]);
    printSet("First(B)", FIRST[2], firstCount[2]);
    printSet("First(C)", FIRST[3], firstCount[3]);
    printSet("First(D)", FIRST[4], firstCount[4]);

    cout << endl << "FOLLOW Sets:" << endl;
    printSet("Follow(S)", FOLLOW[0], followCount[0]);
    printSet("Follow(A)", FOLLOW[1], followCount[1]);
    printSet("Follow(B)", FOLLOW[2], followCount[2]);
    printSet("Follow(C)", FOLLOW[3], followCount[3]);
    printSet("Follow(D)", FOLLOW[4], followCount[4]);

    return 0;
}
