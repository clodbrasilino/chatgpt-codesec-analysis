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
            fprintf(stderr, "Failed to read input.\n");
        } else {
            fprintf(stderr, "No character provided.\n");
        }
        return EXIT_FAILURE;
    }

    if (printf("%d\n", ascii_value((unsigned char)input)) < 0) {
        fprintf(stderr, "Failed to write output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}