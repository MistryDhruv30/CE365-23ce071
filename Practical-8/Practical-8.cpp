#include <iostream>
#include <cstring>
using namespace std;
void constructTable(){


    addEntry('S','a',"AB");
    addEntry('S','b',"AB");

    // A → aA
    addEntry('A','a',"aA");

    // A → ε
    addEntry('A','b',"e");
    addEntry('A','$',"e");

    // B → bB
    addEntry('B','b',"bB");

    // B → ε
    addEntry('B','$',"e");
}

int main(){


    return 0;
}
