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
        return EXIT_FAILURE;
    }

    if (printf("%d\n", ascii_value((unsigned char)input)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}