#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

void count_characters(const char *str, size_t len, int *alphabets, int *digits, int *special_chars) {
    if (str == NULL || alphabets == NULL || digits == NULL || special_chars == NULL) {
        return;
    }

    *alphabets = 0;
    *digits = 0;
    *special_chars = 0;

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isalpha(c)) {
            if (*alphabets < INT_MAX) {
                (*alphabets)++;
            }
        } else if (isdigit(c)) {
            if (*digits < INT_MAX) {
                (*digits)++;
            }
        } else {
            if (*special_chars < INT_MAX) {
                (*special_chars)++;
            }
        }
    }
}

int main(void) {
    char str[256];
    int alphabets = 0, digits = 0, special_chars = 0;

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    size_t len = strnlen(str, sizeof(str));
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }

    count_characters(str, len, &alphabets, &digits, &special_chars);

    printf("Alphabets: %d\n", alphabets);
    printf("Digits: %d\n", digits);
    printf("Special Characters: %d\n", special_chars);

    return EXIT_SUCCESS;
}