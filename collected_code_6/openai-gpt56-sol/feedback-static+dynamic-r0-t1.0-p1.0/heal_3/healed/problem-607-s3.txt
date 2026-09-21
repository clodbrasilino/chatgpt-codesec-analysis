#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_literal(const char *text, size_t text_length,
                        const char *literal, size_t literal_length,
                        size_t *start, size_t *end)
{
    size_t i;

    if (text == NULL || literal == NULL || start == NULL || end == NULL) {
        return -1;
    }

    if (literal_length == 0) {
        *start = 0;
        *end = 0;
        return 1;
    }

    if (literal_length > text_length) {
        return 0;
    }

    for (i = 0; i <= text_length - literal_length; ++i) {
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
    const char *text;
    const char *literal;
    size_t text_length;
    size_t literal_length;
    size_t start;
    size_t end;
    int result;

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        const char *program_name = "literal-search";

        if (argc > 0 && argv != NULL && argv[0] != NULL) {
            program_name = argv[0];
        }

        fprintf(stderr, "Usage: %s <string> <literal>\n", program_name);
        return EXIT_FAILURE;
    }

    text = argv[1];
    literal = argv[2];

    text_length = strnlen(text, SIZE_MAX);
    literal_length = strnlen(literal, SIZE_MAX);

    result = find_literal(text, text_length, literal, literal_length,
                          &start, &end);

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