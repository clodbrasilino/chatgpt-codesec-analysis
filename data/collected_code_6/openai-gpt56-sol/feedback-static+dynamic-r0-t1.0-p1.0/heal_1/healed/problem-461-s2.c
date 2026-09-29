#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_uppercase_stream(FILE *stream)
{
    size_t count = 0;
    int character;

    while ((character = fgetc(stream)) != EOF) {
        if (isupper((unsigned char)character) != 0) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    size_t uppercase_count = count_uppercase_stream(stdin);

    if (ferror(stdin) != 0) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", uppercase_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}