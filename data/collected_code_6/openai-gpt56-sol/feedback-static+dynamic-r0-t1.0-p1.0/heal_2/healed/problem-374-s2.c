#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void swap_chars(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

static int print_permutations(char *string, size_t position, size_t length)
{
    if (position == length) {
        return puts(string) == EOF ? -1 : 0;
    }

    for (size_t i = position; i < length; ++i) {
        swap_chars(&string[position], &string[i]);

        if (print_permutations(string, position + 1U, length) != 0) {
            swap_chars(&string[position], &string[i]);
            return -1;
        }

        swap_chars(&string[position], &string[i]);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "permutations";

        fprintf(stderr, "Usage: %s STRING\n", program);
        return EXIT_FAILURE;
    }

    size_t length = 0U;
    while (argv[1][length] != '\0') {
        if (length == SIZE_MAX - 1U) {
            return EXIT_FAILURE;
        }
        ++length;
    }

    char *string = malloc(length + 1U);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        string[i] = argv[1][i];
    }
    string[length] = '\0';

    int result = print_permutations(string, 0U, length);
    free(string);

    if (result != 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}