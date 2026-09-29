#include <stdio.h>
#include <string.h>

int countCharacter(char* str, char c) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == c) {
            count++;
        }
    }
    return count;
}

int main() {
    char str[] = "Hello, World!";
    char c = 'l';
    int count = countCharacter(str, c);
    printf("The character '%c' appears %d times in the string '%s'.\n", c, count, str);
    return 0;
}