#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 1024

void removeOddIndexChars(char* str) {
    if (str == NULL) return;

    size_t length = strnlen(str, MAX_LENGTH);
    if (length >= MAX_LENGTH) return;

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char tmp[MAX_LENGTH] = {0};

    size_t i, j;
    for(i = 0, j = 1; j < length && str[j] != '\0'; i++, j += 2) {
        tmp[i] = str[j];
    }
    tmp[i] = '\0';

    memmove(str, tmp, i+1);
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_LENGTH] = "abcdefgh";
    removeOddIndexChars(str);
    printf("Result: %s\n", str);

    return 0;
}
