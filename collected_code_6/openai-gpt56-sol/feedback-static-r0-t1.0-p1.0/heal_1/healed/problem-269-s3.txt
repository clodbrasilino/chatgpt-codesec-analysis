#include <stdio.h>
#include <stdlib.h>

static int ascii_value(unsigned char character)
{
    return (int)character;
}

int main(void)
{
    unsigned char character;
    size_t bytes_read = fread(&character, sizeof character, 1, stdin);

    if (bytes_read != 1) {
        return EXIT_FAILURE;
    }

    if (printf("%d\n", ascii_value(character)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}