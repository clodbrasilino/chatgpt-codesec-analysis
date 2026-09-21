#include <stdint.h>
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
        qsort(string, length, sizeof *string, compare_chars);
    }
}

int main(int argc, char *argv[])
{
    const char *program = "program";
    const char *input;
    size_t length;
    char *string;

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    input = argv[1];
    length = strlen(input);

    if (length == SIZE_MAX) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    string = malloc(length + 1U);
    if (string == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (snprintf(string, length + 1U, "%s", input) < 0) {
        fputs("Input copy failed.\n", stderr);
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