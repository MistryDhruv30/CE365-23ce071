#include <stdio.h>
#include <string.h>

int main() {
    char s[100];

    while (1) {
        int i = 0;

        printf("\nEnter String: ");
        fgets(s, sizeof(s), stdin);

        if (s[0] == '\n') {
            printf("Invalid String");
            continue;
        }

        if (s[strlen(s) - 1] == '\n') {
            s[strlen(s) - 1] = '\0';
        }

        while (s[i] == 'a') {
            i++;
        }

        if (s[i] == 'b' && s[i+1] == 'b' && s[i+2] == '\0') {
            printf("Valid String");
        } else {
            printf("Invalid String");
        }
    }

    return 0;
}