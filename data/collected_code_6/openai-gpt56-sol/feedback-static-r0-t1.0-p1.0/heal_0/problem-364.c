#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int minimum_flips(const char *str, size_t *result)
{
    size_t flips_starting_with_zero = 0;
    size_t flips_starting_with_one = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] != '0' && str[i] != '1') {
            return -1;
        }

        char expected_zero = (i % 2 == 0) ? '0' : '1';
        char expected_one = (i % 2 == 0) ? '1' : '0';

        if (str[i] != expected_zero) {
            ++flips_starting_with_zero;
        }

        if (str[i] != expected_one) {
            ++flips_starting_with_one;
        }
    }

    *result = (flips_starting_with_zero < flips_starting_with_one)
                  ? flips_starting_with_zero
                  : flips_starting_with_one;

    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = (capacity == 0) ? 64 : capacity * 2;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) || length == 0) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    size_t flips;
    if (minimum_flips(input, &flips) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", flips) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}