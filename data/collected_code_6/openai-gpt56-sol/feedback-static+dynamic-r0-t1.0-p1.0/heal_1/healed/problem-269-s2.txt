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

    if (input < 0 || input > UCHAR_MAX) {
        fprintf(stderr, "Invalid input value.\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", ascii_value((unsigned char)input));

    return EXIT_SUCCESS;
}