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

        if (print_permutations(string, position + 1, length) != 0) {
            swap_chars(&string[position], &string[i]);
            return -1;
        }

        swap_chars(&string[position], &string[i]);
    }

    return 0;
}

int main(int argc, char *const argv[])
{
    if (argc != 2 || argv == NULL || argv[0] == NULL || argv[1] == NULL) {
        const char *program = "permutations";

        if (argv != NULL && argc > 0 && argv[0] != NULL) {
            program = argv[0];
        }

        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    size_t length = strlen(input);

    if (length == SIZE_MAX) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    char *string = malloc(length + 1);

    if (string == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    memcpy(string, input, length + 1);

    int status = print_permutations(string, 0, length);
    free(string);

    if (status != 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}