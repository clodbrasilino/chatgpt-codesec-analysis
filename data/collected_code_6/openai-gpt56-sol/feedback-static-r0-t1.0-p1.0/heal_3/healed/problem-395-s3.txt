#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int first_non_repeated_character(const unsigned char *data, size_t length,
                                 unsigned char *result)
{
    size_t frequencies[UCHAR_MAX + 1] = {0};
    size_t i;

    if (data == NULL || result == NULL) {
        return 0;
    }

    for (i = 0; i < length; ++i) {
        ++frequencies[data[i]];
    }

    for (i = 0; i < length; ++i) {
        if (frequencies[data[i]] == 1) {
            *result = data[i];
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    unsigned char *input;
    size_t capacity = 128;
    size_t length = 0;
    int ch;
    unsigned char result;

    input = malloc(capacity);
    if (input == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length == capacity) {
            size_t new_capacity;
            unsigned char *new_input;

            if (capacity > SIZE_MAX / 2) {
                fputs("Input is too long.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            new_input = realloc(input, new_capacity);

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

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0) {
        fputs("No input provided.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    if (first_non_repeated_character(input, length, &result)) {
        if (putchar((int)result) == EOF || putchar('\n') == EOF) {
            fputs("Failed to write output.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }
    } else if (puts("No non-repeated character found.") == EOF) {
        fputs("Failed to write output.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}