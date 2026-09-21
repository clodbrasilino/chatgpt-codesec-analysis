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

    const void *terminator = memchr(argv[1], '\0', MAX_LENGTH + 1U);

    if (terminator == NULL) {
        fputs("String is too long\n", stderr);
        return EXIT_FAILURE;
    }

    const size_t length = (const char *)terminator - argv[1];
    char *string = malloc(length + 1U);

    if (string == NULL) {
        fputs("Memory allocation failed\n", stderr);
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