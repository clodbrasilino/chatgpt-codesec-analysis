#include <stdio.h>
#include <string.h>

void removeOddIndexChars(char* str) {
    if (str == NULL) return;

    size_t length = strlen(str);
    size_t i, j;
    char tmp[length+1];

    for(i = 0, j = 1; j < length && str[j] != '\0'; i++, j += 2) {
        tmp[i] = str[j];
    }
    tmp[i] = '\0';

    strcpy(str, tmp);
}

int main() {
    char str[] = "abcdefgh";
    removeOddIndexChars(str);
    printf("Result: %s\n", str);

    return 0;
}