#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static int first_repeated_character(FILE *stream, unsigned char *result)
{
    bool seen[UCHAR_MAX + 1] = { false };

    if (stream == NULL || result == NULL) {
        return -1;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                return -1;
            }
            return 0;
        }

        unsigned char value = (unsigned char)character;

        if (seen[value]) {
            *result = value;
            return 1;
        }

        seen[value] = true;
    }
}

int main(void)
{
    unsigned char repeated = 0;
    int status = first_repeated_character(stdin, &repeated);

    if (status < 0) {
        return EXIT_FAILURE;
    }

    if (status > 0) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else {
        if (puts("No repeated character") == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}