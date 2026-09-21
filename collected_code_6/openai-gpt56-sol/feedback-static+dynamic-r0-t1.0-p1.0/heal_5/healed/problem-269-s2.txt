#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int ascii_value(unsigned char character)
{
    return (int)character;
}

int main(void)
{
    unsigned char character;
    size_t bytes_read = fread(&character, sizeof character, 1, stdin);

    if (bytes_read != 1) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
        } else {
            fprintf(stderr, "No character provided.\n");
        }
        return EXIT_FAILURE;
    }

    if (printf("%d\n", ascii_value(character)) < 0) {
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}