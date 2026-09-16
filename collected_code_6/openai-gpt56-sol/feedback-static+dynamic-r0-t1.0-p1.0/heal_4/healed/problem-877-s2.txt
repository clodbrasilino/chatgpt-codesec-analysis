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

static void sort_string(char *string)
{
    if (string != NULL) {
        qsort(string, strlen(string), sizeof(*string), compare_chars);
    }
}

int main(int argc, char *argv[])
{
    const char *const input = argc > 1 ? argv[1] : NULL;
    char *string;
    size_t length;

    if (argc != 2) {
        const char *const program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

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

    memcpy(string, input, length + 1U);
    sort_string(string);

    if (puts(string) == EOF) {
        free(string);
        fputs("Output failed.\n", stderr);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}