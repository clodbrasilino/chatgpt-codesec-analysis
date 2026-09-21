#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#define BUFFER_SIZE 4096

void count_digits_letters(const char *str, size_t *digits, size_t *letters) {
    if (str == NULL || digits == NULL || letters == NULL) {
        return;
    }

    *digits = 0;
    *letters = 0;

    while (*str != '\0') {
        unsigned char c = (unsigned char)*str;
        if (isdigit(c)) {
            (*digits)++;
        } else if (isalpha(c)) {
            (*letters)++;
        }
        str++;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[BUFFER_SIZE];
    size_t digits = 0;
    size_t letters = 0;
    size_t len;

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = strnlen(str, sizeof(str));
    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return EXIT_FAILURE;
    }

    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    } else if (len == sizeof(str) - 1) {
        int c;
        bool found_newline = false;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != EOF) {
            if (c == '\n') {
                found_newline = true;
                break;
            }
        }
        if (!found_newline && c == EOF && !feof(stdin)) {
            fprintf(stderr, "Error reading input\n");
            return EXIT_FAILURE;
        }
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return EXIT_FAILURE;
    }

    count_digits_letters(str, &digits, &letters);

    printf("Digits: %zu\n", digits);
    printf("Letters: %zu\n", letters);

    return EXIT_SUCCESS;
}