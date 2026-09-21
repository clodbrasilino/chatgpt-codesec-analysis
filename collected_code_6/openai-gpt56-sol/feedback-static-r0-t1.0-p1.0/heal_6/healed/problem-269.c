#include <stdio.h>
#include <stdlib.h>

static int ascii_value(unsigned char character)
{
    return (int)character;
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

    if (printf("%d\n", ascii_value((unsigned char)character)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}