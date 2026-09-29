#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LENGTH 1024

void removeOddIndexChars(char* str) {
    if (str == NULL) return;

    size_t length = strnlen(str, MAX_LENGTH);

    if (length >= MAX_LENGTH) return;

    char* tmp = (char*) calloc(MAX_LENGTH + 1, sizeof(char));

    if (tmp == NULL) return;

    size_t i, j;
    for(i = 0, j = 1; j < length && str[j] != '\0'; i++, j += 2) {
        tmp[i] = str[j];
    }

    tmp[i] = '\0';

    memmove(str, tmp, i+1);

    free(tmp);
}

int main() {
    char* str = (char*) calloc(MAX_LENGTH + 1, sizeof(char));

    if (str == NULL) return -1;

    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120). Risk is low because the source is a  constant string.
     */
    strncpy(str, "abcdefgh", MAX_LENGTH);
    str[MAX_LENGTH] = '\0';

    removeOddIndexChars(str);
    printf("Result: %s\n", str);
    
    free(str);

    return 0;
}