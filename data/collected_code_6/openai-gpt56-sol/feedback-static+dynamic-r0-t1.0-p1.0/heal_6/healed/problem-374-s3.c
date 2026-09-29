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
    enum { MAX_LENGTH = 20 };

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program =
            argv != NULL && argc > 0 && argv[0] != NULL ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    const char *terminator = memchr(argv[1], '\0', MAX_LENGTH + 1U);

    if (terminator == NULL) {
        fputs("String is too long\n", stderr);
        return EXIT_FAILURE;
    }

    size_t length = (size_t)(terminator - argv[1]);

    if (length == SIZE_MAX) {
        fputs("String is too long\n", stderr);
        return EXIT_FAILURE;
    }

    size_t capacity = length + 1U;
    char *string = malloc(capacity);

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