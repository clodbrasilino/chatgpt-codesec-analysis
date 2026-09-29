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
        return printf("%s\n", string) < 0 ? -1 : 0;
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    size_t length = strlen(argv[1]);
    char *string = malloc(length + 1U);

    if (string == NULL) {
        if (fprintf(stderr, "Memory allocation failed\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    memcpy(string, argv[1], length + 1U);

    if (print_permutations(string, 0U, length) != 0) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}