#include <stdio.h>
#include <stdlib.h>

static unsigned int ascii_value(unsigned char character)
{
    return (unsigned int)character;
}

int main(void)
{
    unsigned char buffer[1];
    size_t bytes_read = fread(buffer, sizeof buffer[0], sizeof buffer, stdin);

    if (bytes_read != sizeof buffer) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("No character provided.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (printf("%u\n", ascii_value(buffer[0])) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}