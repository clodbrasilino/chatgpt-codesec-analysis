#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1024

void removeOddIndexChars(char* str) {
    if (str == NULL) return;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t length = strlen(str);
    if (length >= MAX_LENGTH) return;

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char tmp[MAX_LENGTH];

    size_t i, j;
    for(i = 0, j = 1; j < length && str[j] != '\0'; i++, j += 2) {
        tmp[i] = str[j];
    }
    tmp[i] = '\0';

    /* Possible weaknesses found:
     *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
     */
    strncpy(str, tmp, length);
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