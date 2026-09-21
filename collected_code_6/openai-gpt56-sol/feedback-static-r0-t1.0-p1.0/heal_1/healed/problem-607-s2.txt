#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int find_literal(const char *text, const char *literal,
                        size_t *start, size_t *end)
{
    const char *match;
    size_t text_length;
    size_t literal_length;

    if (text == NULL || literal == NULL || start == NULL || end == NULL) {
        return -1;
    }

    text_length = strlen(text);
    literal_length = strlen(literal);

    if (literal_length == 0U) {
        *start = 0U;
        *end = 0U;
        return 1;
    }

    if (literal_length > text_length) {
        return 0;
    }

    match = strstr(text, literal);
    if (match == NULL) {
        return 0;
    }

    *start = (size_t)(match - text);
    *end = *start + literal_length;
    return 1;
}

int main(int argc, char *argv[])
{
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

    result = find_literal(argv[1], argv[2], &start, &end);

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