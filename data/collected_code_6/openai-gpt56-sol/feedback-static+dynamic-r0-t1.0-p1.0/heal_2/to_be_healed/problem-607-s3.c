#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_literal(const char *text, const char *literal,
                        size_t *start, size_t *end)
{
    const char *match;
    size_t text_length;
    size_t literal_length;
    size_t offset;

    if (text == NULL || literal == NULL || start == NULL || end == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    text_length = strlen(text);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    literal_length = strlen(literal);

    match = strstr(text, literal);
    if (match == NULL) {
        return 0;
    }

    offset = (size_t)(match - text);

    if (offset > text_length || literal_length > text_length - offset) {
        return -1;
    }

    *start = offset;
    *end = offset + literal_length;
    return 1;
}

int main(int argc, char *argv[])
{
    size_t start;
    size_t end;
    int result;

    if (argc != 3) {
        const char *program_name = argc > 0 && argv[0] != NULL
                                       ? argv[0]
                                       : "literal-search";

        fprintf(stderr, "Usage: %s <string> <literal>\n", program_name);
        return EXIT_FAILURE;
    }

    result = find_literal(argv[1], argv[2], &start, &end);

    if (result < 0) {
        fputs("Search failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (result == 0) {
        puts("Not found");
        return EXIT_SUCCESS;
    }

    printf("Found at byte range [%zu, %zu)\n", start, end);
    return EXIT_SUCCESS;
}