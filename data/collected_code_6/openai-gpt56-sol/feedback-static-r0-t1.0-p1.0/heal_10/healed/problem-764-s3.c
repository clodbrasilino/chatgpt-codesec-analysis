#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_numeric_values(FILE *stream, int *error)
{
    size_t count = 0;
    int in_number = 0;
    unsigned char buffer[4096];

    if (error == NULL) {
        return 0;
    }

    *error = 0;

    if (stream == NULL) {
        *error = 1;
        return 0;
    }

    for (;;) {
        size_t bytes_read = fread(buffer, sizeof buffer[0], sizeof buffer, stream);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (isdigit((unsigned char)buffer[i])) {
                if (!in_number) {
                    if (count == SIZE_MAX) {
                        *error = 1;
                        return 0;
                    }

                    ++count;
                    in_number = 1;
                }
            } else {
                in_number = 0;
            }
        }

        if (bytes_read < sizeof buffer) {
            if (ferror(stream)) {
                *error = 1;
                return 0;
            }

            break;
        }
    }

    return count;
}

int main(void)
{
    int error;
    size_t count = count_numeric_values(stdin, &error);

    if (error != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}