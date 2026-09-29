#include <stdio.h>
#include <stdlib.h>

static unsigned int ascii_value(unsigned char character)
{
    return (unsigned int)character;
}

int main(void)
{
    int character = fgetc(stdin);

    if (character == EOF) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (printf("%u\n", ascii_value((unsigned char)character)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}