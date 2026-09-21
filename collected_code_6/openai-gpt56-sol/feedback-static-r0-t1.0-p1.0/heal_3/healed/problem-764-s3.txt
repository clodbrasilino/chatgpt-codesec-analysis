#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_numeric_values(FILE *stream, int *error)
{
    size_t count = 0;
    int in_number = 0;
    int ch;

    *error = 0;

    while ((ch = fgetc(stream)) != EOF) {
        if (isdigit((unsigned char)ch)) {
            if (!in_number) {
                ++count;
                in_number = 1;
            }
        } else {
            in_number = 0;
        }
    }

    if (ferror(stream)) {
        *error = 1;
    }

    return count;
}

int main(void)
{
    int error;
    size_t count = count_numeric_values(stdin, &error);

    if (error) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}