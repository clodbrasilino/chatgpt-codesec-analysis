#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_uppercase_stream(FILE *stream, size_t *count)
{
    size_t total = 0;
    int ch;

    if (stream == NULL || count == NULL) {
        return -1;
    }

    while ((ch = fgetc(stream)) != EOF) {
        if (isupper((unsigned char)ch)) {
            if (total == SIZE_MAX) {
                return -1;
            }
            ++total;
        }
    }

    if (ferror(stream)) {
        return -1;
    }

    *count = total;
    return 0;
}

int main(void)
{
    size_t uppercase_count = 0;

    if (count_uppercase_stream(stdin, &uppercase_count) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", uppercase_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}