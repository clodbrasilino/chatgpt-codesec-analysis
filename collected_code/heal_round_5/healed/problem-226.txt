#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1024

void removeOddIndexChars(char* str) {
    if (str == NULL) return;

    size_t length = strlen(str);
    if (length >= MAX_LENGTH) return;

    char tmp[MAX_LENGTH];

    size_t i, j;
    for(i = 0, j = 1; j < length && str[j] != '\0'; i++, j += 2) {
        tmp[i] = str[j];
    }
    tmp[i] = '\0';

    strncpy(str, tmp, length);
}

int main() {
    char str[MAX_LENGTH] = "abcdefgh";
    removeOddIndexChars(str);
    printf("Result: %s\n", str);

    return 0;
}