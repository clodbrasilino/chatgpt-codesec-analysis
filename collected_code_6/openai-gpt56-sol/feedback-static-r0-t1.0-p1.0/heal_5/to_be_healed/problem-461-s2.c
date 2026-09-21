#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_uppercase_stream(FILE *stream, int *read_error)
{
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

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        unsigned char buffer[4096];
        size_t bytes_read = fread(buffer, 1, sizeof buffer, stream);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (isupper(buffer[i]) != 0) {
                if (count == SIZE_MAX) {
                    if (read_error != NULL) {
                        *read_error = 1;
                    }
                    return 0;
                }
                ++count;
            }
        }

        if (bytes_read < sizeof buffer) {
            if (ferror(stream) != 0) {
                if (read_error != NULL) {
                    *read_error = 1;
                }
                return 0;
            }

            if (feof(stream) != 0) {
                break;
            }
        }
    }

    return count;
}

int main(void)
{
    int read_error;
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