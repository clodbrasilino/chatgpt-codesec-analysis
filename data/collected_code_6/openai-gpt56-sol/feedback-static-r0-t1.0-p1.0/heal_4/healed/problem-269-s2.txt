#include <stdio.h>
#include <stdlib.h>

static int ascii_value(unsigned char character)
{
    return (int)character;
}

int main(void)
{
    int input = getchar();

    if (input == EOF) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("No character provided.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    if (printf("%u\n", (unsigned int)ascii_value((unsigned char)input)) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}