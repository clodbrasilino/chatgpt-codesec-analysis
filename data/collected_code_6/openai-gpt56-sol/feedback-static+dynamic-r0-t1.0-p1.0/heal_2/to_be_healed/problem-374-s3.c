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

int main(int argc, char *const argv[])
{
    if (argc != 2) {
        const char *program = argc > 0 && argv[0] != NULL ? argv[0] : "program";
        (void)fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    if (argv[1] == NULL) {
        (void)fprintf(stderr, "Invalid string argument\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    const size_t length = strlen(argv[1]);

    if (length == SIZE_MAX) {
        (void)fprintf(stderr, "String is too long\n");
        return EXIT_FAILURE;
    }

    char *string = malloc(length + 1U);
    if (string == NULL) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(string, argv[1]);

    const int result = print_permutations(string, 0U, length);
    free(string);

    if (result != 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}