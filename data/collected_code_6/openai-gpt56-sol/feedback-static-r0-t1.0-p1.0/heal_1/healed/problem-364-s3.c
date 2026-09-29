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
        if (str[i] != '0' && str[i] != '1') {
            return 0;
        }

        if (str[i] != ((i & 1U) == 0U ? '0' : '1')) {
            ++flips_starting_with_zero;
        }

        if (str[i] != ((i & 1U) == 0U ? '1' : '0')) {
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
    enum { MAX_INPUT_LENGTH = 1048576 };
    char *input = malloc((size_t)MAX_INPUT_LENGTH + 2U);
    size_t length;
    size_t flips;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, MAX_INPUT_LENGTH + 2, stdin) == NULL) {
        if (ferror(stdin)) {
            free(input);
            return EXIT_FAILURE;
        }

        input[0] = '\0';
    }

    for (length = 0; input[length] != '\0' && input[length] != '\n'; ++length) {
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        free(input);
        return EXIT_FAILURE;
    }

    if (!minimum_flips(input, length, &flips)) {
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