#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_chars(const void *left, const void *right)
{
    const unsigned char a = *(const unsigned char *)left;
    const unsigned char b = *(const unsigned char *)right;

    return (a > b) - (a < b);
}

static void sort_string(char *string, size_t length)
{
    if (string != NULL && length > 1U) {
        qsort(string, length, sizeof(*string), compare_chars);
    }
}

int main(int argc, char *argv[])
{
    const char *program;
    const char *input;
    char *string;
    size_t length;

    program = (argc > 0 && argv != NULL && argv[0] != NULL)
                  ? argv[0]
                  : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    input = argv[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(input);

    if (length == SIZE_MAX) {
        fputs("Input string is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    string = malloc(length + 1U);
    if (string == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (snprintf(string, length + 1U, "%s", input) < 0) {
        fputs("String copy failed.\n", stderr);
        free(string);
        return EXIT_FAILURE;
    }

    sort_string(string, length);

    if (puts(string) == EOF) {
        fputs("Output failed.\n", stderr);
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}