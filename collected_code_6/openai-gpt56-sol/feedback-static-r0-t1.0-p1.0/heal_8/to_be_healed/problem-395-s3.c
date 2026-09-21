#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int first_non_repeated_character(const unsigned char *data, size_t length,
                                 unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};

    if (data == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (frequencies[data[i]] == SIZE_MAX) {
            return 0;
        }
        ++frequencies[data[i]];
    }

    for (size_t i = 0; i < length; ++i) {
        if (frequencies[data[i]] == 1) {
            *result = data[i];
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    unsigned char result;
    unsigned char *input = malloc(capacity);

    if (input == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    while (length < SIZE_MAX) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == capacity) {
            if (capacity > SIZE_MAX / 2) {
                fputs("Input is too long.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            size_t new_capacity = capacity * 2;
            unsigned char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                fputs("Memory allocation failed.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)ch;
    }

    if (length == SIZE_MAX) {
        fputs("Input is too long.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (length == 0) {
        fputs("No input provided.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (first_non_repeated_character(input, length, &result)) {
        if (fputc((int)result, stdout) == EOF ||
            fputc('\n', stdout) == EOF) {
            fputs("Failed to write output.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }
    } else {
        if (fputs("No non-repeated character found.\n", stdout) == EOF) {
            fputs("Failed to write output.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }
    }

    free(input);
    return EXIT_SUCCESS;
}