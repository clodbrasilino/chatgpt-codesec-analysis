#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_uppercase_stream(FILE *stream, size_t *count)
{
    unsigned char *buffer;
    size_t total = 0;
    size_t bytes_read;
    const size_t buffer_size = 4096;

    if (stream == NULL || count == NULL) {
        return -1;
    }

    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        return -1;
    }

    while ((bytes_read = fread(buffer, 1, buffer_size, stream)) != 0) {
        for (size_t i = 0; i < bytes_read; ++i) {
            if (isupper((int)buffer[i])) {
                if (total == SIZE_MAX) {
                    free(buffer);
                    return -1;
                }
                ++total;
            }
        }
    }

    if (ferror(stream)) {
        free(buffer);
        return -1;
    }

    free(buffer);
    *count = total;
    return 0;
}

int main(void)
{
    size_t uppercase_count = 0;

    if (count_uppercase_stream(stdin, &uppercase_count) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", uppercase_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}