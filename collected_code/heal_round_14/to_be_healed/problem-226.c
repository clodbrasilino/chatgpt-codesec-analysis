#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LENGTH 1024

void removeOddIndexChars(char* str, size_t max_len) {
    if (str == NULL || max_len == 0) return;

    size_t length = strnlen(str, max_len);
    if (length > max_len - 1) return;

    char* tmp = (char*) calloc(length + 1, sizeof(char));
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
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char str[MAX_LENGTH + 1] = {0};
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    if(MAX_LENGTH >= strlen("abcdefgh")) {
        /* Possible weaknesses found:
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120). Risk is low because the source is a  constant string.
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        strncpy(str, "abcdefgh", strlen("abcdefgh"));
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        str[strlen("abcdefgh")] = '\0';
    }
    
    removeOddIndexChars(str, MAX_LENGTH);
    printf("Result: %s\n", str);

    return 0;
}