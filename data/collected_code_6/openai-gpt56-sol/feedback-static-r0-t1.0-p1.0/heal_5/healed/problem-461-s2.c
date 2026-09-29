#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_uppercase_stream(FILE *stream, int *read_error)
{
    unsigned char buffer[4096];
    size_t count = 0;

    if (read_error != NULL) {
        *read_error = 0;
    }

    if (stream == NULL) {
        if (read_error != NULL) {
            *read_error = 1;
        }
        return 0;
    }

    while (!feof(stream)) {
        size_t bytes_read = fread(buffer, sizeof buffer[0], sizeof buffer, stream);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (isupper((int)buffer[i]) != 0) {
                if (count == SIZE_MAX) {
                    if (read_error != NULL) {
                        *read_error = 1;
                    }
                    return 0;
                }
                ++count;
            }
        }

        if (ferror(stream)) {
            if (read_error != NULL) {
                *read_error = 1;
            }
            return 0;
        }
    }

    return count;
}

int main(void)
{
    int read_error = 0;
    size_t count = count_uppercase_stream(stdin, &read_error);

    if (read_error != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}