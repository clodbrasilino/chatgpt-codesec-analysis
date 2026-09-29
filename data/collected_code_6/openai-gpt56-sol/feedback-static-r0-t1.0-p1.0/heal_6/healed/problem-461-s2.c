#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_uppercase_stream(FILE *stream, int *read_error)
{
    unsigned char *buffer = NULL;
    const size_t buffer_size = 4096;
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

    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        if (read_error != NULL) {
            *read_error = 1;
        }
        return 0;
    }

    for (;;) {
        size_t bytes_read = fread(buffer, 1, buffer_size, stream);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (isupper((int)buffer[i]) != 0) {
                if (count == SIZE_MAX) {
                    free(buffer);
                    if (read_error != NULL) {
                        *read_error = 1;
                    }
                    return 0;
                }
                ++count;
            }
        }

        if (bytes_read < buffer_size) {
            if (ferror(stream)) {
                free(buffer);
                if (read_error != NULL) {
                    *read_error = 1;
                }
                return 0;
            }

            if (feof(stream)) {
                break;
            }
        }
    }

    free(buffer);
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