#include <stdio.h>

void removeOddIndexChars(char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    
    int i, j;
    for (i = 0, j = 1; i < length && j < length; i += 2, j += 2) {
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