#include <stdio.h>
#include <string.h>
#include <ctype.h>

int countCharsSamePosAsInAlphabet(char* str) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++) {
        char c = tolower(str[i]);
        if (i+1 == c-'a'+1) {
            count++;
        }
    }
    return count;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';
    int count = countCharsSamePosAsInAlphabet(str);
    printf("Number of characters at the same position as in English alphabet: %d\n", count);
    return 0;
}