#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_literal(const char *text, size_t text_length,
                        const char *literal, size_t literal_length,
                        size_t *start, size_t *length)
{
    size_t i;

    if (text == NULL || literal == NULL || start == NULL || length == NULL) {
        return -1;
    }

    if (literal_length == 0) {
        *start = 0;
        *length = 0;
        return 1;
    }

    if (literal_length > text_length) {
        return 0;
    }

    for (i = 0; i <= text_length - literal_length; ++i) {
        if (memcmp(text + i, literal, literal_length) == 0) {
            *start = i;
            *length = literal_length;
            return 1;
        }
    }

    return 0;
}

int main(int argc, char *const argv[])
{
    const char *text;
    const char *literal;
    size_t text_length;
    size_t literal_length;
    size_t start;
    size_t length;
    int result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <literal>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    text = argv[1];
    literal = argv[2];

    if (text == NULL || literal == NULL) {
        fputs("Invalid argument\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    text_length = strlen(text);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    literal_length = strlen(literal);

    result = find_literal(text, text_length, literal, literal_length,
                          &start, &length);

    if (result < 0) {
        fputs("Search failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (result == 0) {
        puts("Not found");
        return EXIT_SUCCESS;
    }

    printf("Found at index %zu, length %zu\n", start, length);
    return EXIT_SUCCESS;
}