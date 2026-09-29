#include <stdio.h>

void replaceCharacters(char *str, char oldChar, char newChar) {
    if (str == NULL) {
        return;
    }
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == oldChar) {
            str[i] = newChar;
        }
    }
}

int main() {
    char str[] = "Hello World!";
    char oldChar = 'l';
    char newChar = 'X';
    
    replaceCharacters(str, oldChar, newChar);
    
    printf("%s\n", str);
    
    return 0;
}