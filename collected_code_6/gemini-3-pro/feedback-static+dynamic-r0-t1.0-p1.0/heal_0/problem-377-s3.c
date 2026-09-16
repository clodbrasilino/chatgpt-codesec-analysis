#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removeCharacter(char *str, char charToRemove) {
    if (str == NULL) {
        return;
    }

    int i = 0;
    int j = 0;

    while (str[i] != '\0') {
        if (str[i] != charToRemove) {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    char inputString[] = "Hello, World!";
    char targetChar = 'o';

    removeCharacter(inputString, targetChar);

    printf("%s\n", inputString);

    return 0;
}