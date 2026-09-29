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

    if (putchar('0' + (input / 100)) == EOF && input >= 100) {
        return EXIT_FAILURE;
    }

    if (input >= 100) {
        if (putchar('0' + ((input / 10) % 10)) == EOF ||
            putchar('0' + (input % 10)) == EOF ||
            putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else if (printf("%d\n", ascii_value((unsigned char)input)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}