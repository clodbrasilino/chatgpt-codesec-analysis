#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_flips(const char *str, size_t length, size_t *result)
{
    size_t flips_starting_with_zero = 0;
    size_t flips_starting_with_one = 0;

    if (str == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        char expected_zero = (i % 2U == 0U) ? '0' : '1';
        char expected_one = (i % 2U == 0U) ? '1' : '0';

        if (str[i] != '0' && str[i] != '1') {
            return 0;
        }

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

    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    size_t flips = 0;
    int ch = EOF;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == capacity) {
            char *resized;
            size_t new_capacity;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1U);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    if (!minimum_flips(input, length, &flips)) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%zu\n", flips) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}