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

int main(int argc, const char *const argv[])
{
    size_t text_length;
    size_t literal_length;
    size_t start;
    size_t end;
    int result;

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <string> <literal>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "program");
        return EXIT_FAILURE;
    }

    text_length = strlen(argv[1]);
    literal_length = strlen(argv[2]);

    result = find_literal(argv[1], text_length, argv[2], literal_length,
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