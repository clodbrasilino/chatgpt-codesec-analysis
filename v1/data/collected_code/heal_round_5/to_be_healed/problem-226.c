#include <stdio.h>
#include <string.h>

void removeOddIndexChars(char* str) {
    if (str == NULL) return;

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    size_t length = strlen(str);
    size_t i, j;
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char tmp[length+1];

    for(i = 0, j = 1; j < length && str[j] != '\0'; i++, j += 2) {
        tmp[i] = str[j];
    }
    tmp[i] = '\0';

    /* Possible weaknesses found:
     *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
     */
    strcpy(str, tmp);
}

int main() {
    char str[] = "abcdefgh";
    removeOddIndexChars(str);
    printf("Result: %s\n", str);

    return 0;
}