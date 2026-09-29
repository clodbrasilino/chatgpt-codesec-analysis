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

static int print_permutations(char *string, size_t start, size_t length)
{
    if (start == length) {
        return puts(string) == EOF ? -1 : 0;
    }

    for (size_t i = start; i < length; ++i) {
        swap_chars(&string[start], &string[i]);

        if (print_permutations(string, start + 1U, length) != 0) {
            swap_chars(&string[start], &string[i]);
            return -1;
        }

        swap_chars(&string[start], &string[i]);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2 || argv == NULL || argv[0] == NULL || argv[1] == NULL) {
        const char *program = "program";

        if (argv != NULL && argv[0] != NULL) {
            program = argv[0];
        }

        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    size_t length = strnlen(argv[1], SIZE_MAX);

    if (length == SIZE_MAX) {
        fputs("Input is too large or not null-terminated\n", stderr);
        return EXIT_FAILURE;
    }

    char *string = malloc(length + 1U);
    if (string == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0U) {
        memcpy(string, argv[1], length);
    }
    string[length] = '\0';

    int result = print_permutations(string, 0U, length);
    free(string);

    if (result != 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}