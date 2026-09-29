#include <stdio.h>
#include <string.h>

void removeOddIndexChars(char* str) {
    int length = strlen(str);

    int i, j;
    for (i = 0, j = 1; j < length; i++, j += 2) {
        str[i] = str[j];
    }
    str[i] = '\0';
}

int main() {
    char str[] = "abcdefgh";
    removeOddIndexChars(str);
    printf("Result: %s\n", str);

    return 0;
}