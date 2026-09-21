#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_first_max_even_word(const char *str, char *result) {
    if (str == NULL || result == NULL) {
        return -1;
    }

    int max_len = 0;
    int found = 0;
    const char *start = NULL;

    while (*str != '\0') {
        while (*str == ' ') {
            str++;
        }

        if (*str == '\0') {
            break;
        }

        const char *word_start = str;
        while (*str != '\0' && *str != ' ') {
            str++;
        }

        int len = str - word_start;

        if (len % 2 == 0) {
            if (len > max_len) {
                max_len = len;
                start = word_start;
                found = 1;
            }
        }
    }

    if (found) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, start, max_len);
        result[max_len] = '\0';
        return max_len;
    }

    result[0] = '\0';
    return 0;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'input' can be declared as const array [constVariable]
     */
    char input[] = "This is a test string with some even and odd words";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[256];
    int len = find_first_max_even_word(input, result);

    if (len > 0) {
        printf("%s\n", result);
    } else {
        printf("No even length word found\n");
    }

    return 0;
}