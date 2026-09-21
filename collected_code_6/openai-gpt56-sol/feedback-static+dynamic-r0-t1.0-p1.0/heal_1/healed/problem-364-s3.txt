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

        if (str[i] != ((i % 2U == 0U) ? '0' : '1')) {
            ++flips_starting_with_zero;
        }

        if (str[i] != ((i % 2U == 0U) ? '1' : '0')) {
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
    char input[4096];
    size_t length;
    size_t flips;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        input[0] = '\0';
    }

    length = 0;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length < sizeof input && input[length] == '\n') {
        input[length] = '\0';
    } else if (length == sizeof input - 1U && input[length] == '\0') {
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return EXIT_FAILURE;
        }
        if (ch == EOF && ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    if (!minimum_flips(input, length, &flips)) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", flips) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}