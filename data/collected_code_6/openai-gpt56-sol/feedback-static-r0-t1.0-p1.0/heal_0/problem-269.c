#include <stdio.h>
#include <stdlib.h>

int ascii_value(unsigned char character)
{
    return (int)character;
}

int main(void)
{
    int input = getchar();

    if (input == EOF) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    printf("%d\n", ascii_value((unsigned char)input));

    if (ferror(stdout)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}