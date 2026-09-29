#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p;
    size_t integer_digits = 0;

    if (text == NULL || *text == '\0') {
        return false;
    }

    p = (const unsigned char *)text;

    if (*p == '+' || *p == '-') {
        ++p;
    }

    while (*p >= '0' && *p <= '9') {
        ++integer_digits;
        ++p;
    }

    if (integer_digits == 0 || *p != '.') {
        return false;
    }

    ++p;

    return p[0] >= '0' && p[0] <= '9' &&
           p[1] >= '0' && p[1] <= '9' &&
           p[2] == '\0';
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length > SIZE_MAX - 2) {
            free(input);
            fputs("Input too long\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fputs("Input too long\n", stderr);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Memory allocation error\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0) {
        free(input);
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Memory allocation error\n", stderr);
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");

    free(input);
    return EXIT_SUCCESS;
}