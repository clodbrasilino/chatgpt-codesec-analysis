#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define BUFFER_SIZE 100

void count_digits_letters(const char *str, int *digits, int *letters) {
    if (str == NULL || digits == NULL || letters == NULL) {
        return;
    }

    *digits = 0;
    *letters = 0;

    while (*str != '\0') {
        if (isdigit((unsigned char)*str)) {
            (*digits)++;
        } else if (isalpha((unsigned char)*str)) {
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
    int digits = 0;
    int letters = 0;
    size_t len;

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = strnlen(str, sizeof(str));
    if (len == 0) {
        fprintf(stderr, "Empty input\n");
        return 1;
    }

    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    } else if (len == sizeof(str) - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        fprintf(stderr, "Input too long\n");
        return 1;
    }

    count_digits_letters(str, &digits, &letters);

    printf("Digits: %d\n", digits);
    printf("Letters: %d\n", letters);

    return 0;
}