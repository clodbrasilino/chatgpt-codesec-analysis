#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int count_digits_and_letters(const unsigned char *data, size_t length,
                             size_t *digits, size_t *letters)
{
    size_t i;

    if (data == NULL || digits == NULL || letters == NULL) {
        return -1;
    }

    *digits = 0;
    *letters = 0;

    for (i = 0; i < length; ++i) {
        if (isdigit((int)data[i])) {
            ++*digits;
        } else if (isalpha((int)data[i])) {
            ++*letters;
        }
    }

    return 0;
}

int main(void)
{
    unsigned char *input;
    size_t length = 0;
    size_t capacity = 128;
    size_t digits;
    size_t letters;

    input = malloc(capacity);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            unsigned char *new_input;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                fprintf(stderr, "Input is too large.\n");
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fprintf(stderr, "Memory allocation failed.\n");
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (count_digits_and_letters(input, length, &digits, &letters) != 0) {
        free(input);
        fprintf(stderr, "Invalid argument.\n");
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("Digits: %zu\nLetters: %zu\n", digits, letters) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}