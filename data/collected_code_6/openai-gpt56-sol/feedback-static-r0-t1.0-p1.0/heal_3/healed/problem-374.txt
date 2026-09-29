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
        return printf("%s\n", string) < 0 ? -1 : 0;
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

int main(int argc, char *argv[])
{
    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program =
            argv != NULL && argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    if (strlen(argv[1]) == SIZE_MAX) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    size_t capacity = strlen(argv[1]) + 1;
    char *string = malloc(capacity);

    if (string == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    int result = snprintf(string, capacity, "%s", argv[1]);
    if (result < 0 || (size_t)result >= capacity) {
        fputs("Failed to copy input\n", stderr);
        free(string);
        return EXIT_FAILURE;
    }

    int status = print_permutations(string, 0, (size_t)result);
    free(string);

    if (status != 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}