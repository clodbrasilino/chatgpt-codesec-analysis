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
    char *string;
    size_t length;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    length = strlen(argv[1]);

    if (length > SIZE_MAX - 1U) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    string = malloc(length + 1U);
    if (string == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    memcpy(string, argv[1], length);
    string[length] = '\0';

    sort_string(string, length);

    if (puts(string) == EOF) {
        fputs("Output failed.\n", stderr);
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}