#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int find_literal(const char *text, size_t text_length,
                        const char *literal, size_t literal_length,
                        size_t *start, size_t *end)
{
    size_t i;

    if (text == NULL || literal == NULL || start == NULL || end == NULL) {
        return -1;
    }

    if (literal_length == 0U) {
        *start = 0U;
        *end = 0U;
        return 1;
    }

    if (literal_length > text_length) {
        return 0;
    }

    for (i = 0U; i <= text_length - literal_length; ++i) {
        if (memcmp(text + i, literal, literal_length) == 0) {
            *start = i;
            *end = i + literal_length;
            return 1;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    size_t text_length;
    size_t literal_length;
    size_t start;
    size_t end;
    int result;
    const char *program_name;

    program_name = (argc > 0 && argv != NULL && argv[0] != NULL)
                       ? argv[0]
                       : "program";

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <string> <literal>\n", program_name);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    text_length = strlen(argv[1]);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    literal_length = strlen(argv[2]);

    result = find_literal(argv[1], text_length,
                          argv[2], literal_length,
                          &start, &end);

    if (result < 0) {
        fputs("Search failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (result == 0) {
        puts("Pattern not found");
        return EXIT_SUCCESS;
    }

    printf("Pattern found at [%zu, %zu)\n", start, end);
    return EXIT_SUCCESS;
}