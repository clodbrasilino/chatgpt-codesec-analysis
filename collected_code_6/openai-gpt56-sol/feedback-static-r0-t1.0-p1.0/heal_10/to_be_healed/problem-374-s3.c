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
        const char *program =
            argv != NULL && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(argv[1]);

    if (length == SIZE_MAX) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    size_t capacity = length + 1U;
    char *string = malloc(capacity);

    if (string == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    int written = snprintf(string, capacity, "%s", argv[1]);

    if (written < 0 || (size_t)written >= capacity) {
        fputs("Failed to copy input\n", stderr);
        free(string);
        return EXIT_FAILURE;
    }

    int result = print_permutations(string, 0U, length);
    free(string);

    if (result != 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}