#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LENGTH 1024

void removeOddIndexChars(char* str, size_t max_len) {
    if (str == NULL || max_len == 0) return;

    size_t length = strnlen(str, max_len);
    if (length >= max_len) return;

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

    char input[] = "abcdefgh";
    size_t input_size = sizeof(input) - 1;  // excluding null terminator

    if(MAX_LENGTH >= input_size) {
        /* Possible weaknesses found:
         *   Does not check for buffer overflows when copying to destination (CWE-120).  Make sure destination can always hold the source data.
         */
        memcpy(str, input, input_size);
        str[input_size] = '\0';
    }

    removeOddIndexChars(str, MAX_LENGTH);
    printf("Result: %s\n", str);

    return 0;
}