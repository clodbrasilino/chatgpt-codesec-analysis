#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void swap_chars(char *a, char *b)
{
    const char temp = *a;
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

int main(int argc, char *const argv[])
{
    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s STRING\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    const size_t length = strlen(argv[1]);

    if (length == SIZE_MAX) {
        return EXIT_FAILURE;
    }

    char *string = malloc(length + 1U);
    if (string == NULL) {
        return EXIT_FAILURE;
    }

    memcpy(string, argv[1], length + 1U);

    const int result = print_permutations(string, 0U, length);

    free(string);

    if (result != 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}