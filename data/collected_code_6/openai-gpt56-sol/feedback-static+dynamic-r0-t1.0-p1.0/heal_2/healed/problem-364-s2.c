#include <stdio.h>
#include <stdlib.h>

static int minimum_flips(const char *str, size_t length, size_t *result)
{
    size_t flips_starting_with_zero = 0;
    size_t flips_starting_with_one = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (str[i] != '0' && str[i] != '1') {
            return -1;
        }

        char expected_zero = (i % 2U == 0U) ? '0' : '1';
        char expected_one = (i % 2U == 0U) ? '1' : '0';

        if (str[i] != expected_zero) {
            ++flips_starting_with_zero;
        }

        if (str[i] != expected_one) {
            ++flips_starting_with_one;
        }
    }

    *result = flips_starting_with_zero < flips_starting_with_one
                  ? flips_starting_with_zero
                  : flips_starting_with_one;

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    size_t flips = 0;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 128U : capacity * 2U;

            if (new_capacity <= capacity || new_capacity > SIZE_MAX / sizeof(*input)) {
                free(input);
                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }

            char *new_input = realloc(input, new_capacity * sizeof(*input));
            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    if (minimum_flips(input, length, &flips) != 0) {
        free(input);
        fputs("Input must contain only binary characters.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%zu\n", flips) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}