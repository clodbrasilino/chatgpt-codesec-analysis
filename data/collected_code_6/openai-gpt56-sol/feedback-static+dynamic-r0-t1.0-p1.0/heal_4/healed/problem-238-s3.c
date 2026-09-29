#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

static int count_non_empty_substrings(uint64_t length, uint64_t *count)
{
    uint64_t first;
    uint64_t second;

    if (count == NULL || length == UINT64_MAX) {
        return -1;
    }

    first = length;
    second = length + UINT64_C(1);

    if ((first & UINT64_C(1)) == 0) {
        first /= UINT64_C(2);
    } else {
        second /= UINT64_C(2);
    }

    if (second != 0 && first > UINT64_MAX / second) {
        return -1;
    }

    *count = first * second;
    return 0;
}

int main(void)
{
    uint64_t length = 0;
    uint64_t count = 0;
    char buffer[4096];

    for (;;) {
        size_t bytes_read = fread(buffer, 1, sizeof buffer, stdin);

        for (size_t i = 0; i < bytes_read; ++i) {
            if (buffer[i] == '\n') {
                goto input_complete;
            }

            if (length == UINT64_MAX) {
                return EXIT_FAILURE;
            }

            ++length;
        }

        if (bytes_read < sizeof buffer) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }

            if (feof(stdin)) {
                break;
            }
        }
    }

input_complete:
    if (count_non_empty_substrings(length, &count) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}