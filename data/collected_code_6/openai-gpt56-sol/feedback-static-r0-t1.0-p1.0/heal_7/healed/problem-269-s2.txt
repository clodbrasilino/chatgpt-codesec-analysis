#include <stdio.h>
#include <stdlib.h>

static unsigned int ascii_value(unsigned char character)
{
    return (unsigned int)character;
}

int main(void)
{
    int character = getchar();

    if (character == EOF) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("No character provided.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (printf("%u\n", ascii_value((unsigned char)character)) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}