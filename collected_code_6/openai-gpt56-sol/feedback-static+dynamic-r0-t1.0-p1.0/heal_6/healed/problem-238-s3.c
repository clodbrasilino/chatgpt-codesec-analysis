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
    char buffer[4096];
    uint64_t length = 0;
    uint64_t count;
    int line_complete = 0;

    while (!line_complete && fgets(buffer, sizeof buffer, stdin) != NULL) {
        size_t i;

        for (i = 0; buffer[i] != '\0'; ++i) {
            if (buffer[i] == '\n') {
                line_complete = 1;
                break;
            }

            if (length == UINT64_MAX) {
                return EXIT_FAILURE;
            }

            ++length;
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (count_non_empty_substrings(length, &count) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}