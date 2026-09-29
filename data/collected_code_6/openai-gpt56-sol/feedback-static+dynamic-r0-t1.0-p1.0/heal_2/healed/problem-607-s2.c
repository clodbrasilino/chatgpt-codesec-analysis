#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_literal(const char *text, const char *literal,
                        size_t *start, size_t *end)
{
    const char *match;
    size_t offset;
    size_t literal_length;

    if (text == NULL || literal == NULL || start == NULL || end == NULL) {
        return -1;
    }

    literal_length = strlen(literal);
    match = strstr(text, literal);

    if (match == NULL) {
        return 0;
    }

    offset = (size_t)(match - text);
    *start = offset;
    *end = offset + literal_length;

    return 1;
}

int main(int argc, char *const argv[])
{
    size_t start;
    size_t end;
    int result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <literal>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
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