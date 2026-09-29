#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t max_uppercase_run(FILE *stream, int *error)
{
    size_t maximum = 0;
    size_t current = 0;
    int ch;

    if (error != NULL) {
        *error = 0;
    }

    if (stream == NULL) {
        if (error != NULL) {
            *error = 1;
        }
        return 0;
    }

    for (;;) {
        ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream)) {
                if (error != NULL) {
                    *error = 1;
                }
                return 0;
            }
            break;
        }

        if (isupper((unsigned char)ch) != 0) {
            if (current == SIZE_MAX) {
                if (error != NULL) {
                    *error = 1;
                }
                return 0;
            }

            ++current;

            if (current > maximum) {
                maximum = current;
            }
        } else {
            current = 0;
        }
    }

    return maximum;
}

int main(void)
{
    int error = 0;
    size_t maximum = max_uppercase_run(stdin, &error);

    if (error != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", maximum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}