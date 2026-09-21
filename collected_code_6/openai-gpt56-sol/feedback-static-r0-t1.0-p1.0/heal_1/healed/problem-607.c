#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_literal(const char *text, const char *literal,
                        size_t *start, size_t *length)
{
    const char *match;
    size_t literal_length;

    if (text == NULL || literal == NULL || start == NULL || length == NULL) {
        return -1;
    }

    literal_length = strlen(literal);
    match = strstr(text, literal);

    if (match == NULL) {
        return 0;
    }

    *start = (size_t)(match - text);
    *length = literal_length;

    return 1;
}

int main(int argc, char *const argv[])
{
    size_t start;
    size_t length;
    int result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <literal>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    result = find_literal(argv[1], argv[2], &start, &length);

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