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

    const char *input = argv[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);

    if (length > SIZE_MAX - 1) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    char *string = malloc(length + 1);
    if (string == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(string, input, length + 1);

    int status = print_permutations(string, 0, length);
    free(string);

    if (status != 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}