#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_uppercase_stream(FILE *stream, size_t *count)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[4096];
    size_t total = 0;
    size_t bytes_read;

    if (stream == NULL || count == NULL) {
        return -1;
    }

    while ((bytes_read = fread(buffer, 1, sizeof buffer, stream)) > 0) {
        for (size_t i = 0; i < bytes_read; ++i) {
            if (isupper(buffer[i])) {
                if (total == SIZE_MAX) {
                    return -1;
                }
                ++total;
            }
        }
    }

    if (ferror(stream)) {
        return -1;
    }

    *count = total;
    return 0;
}

int main(void)
{
    size_t uppercase_count;

    if (count_uppercase_stream(stdin, &uppercase_count) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", uppercase_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}