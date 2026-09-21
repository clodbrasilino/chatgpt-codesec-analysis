#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

static int count_non_empty_substrings(uint64_t length, uint64_t *count)
{
    uint64_t first;
    uint64_t second;

    if (count == NULL) {
        return -1;
    }

    first = length;
    second = length + 1U;

    if (second == 0U) {
        return -1;
    }

    if ((first & 1U) == 0U) {
        first /= 2U;
    } else {
        second /= 2U;
    }

    if (second != 0U && first > UINT64_MAX / second) {
        return -1;
    }

    *count = first * second;
    return 0;
}

int main(void)
{
    uint64_t length = 0U;
    uint64_t count;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == UINT64_MAX) {
            return EXIT_FAILURE;
        }
        ++length;
    }

    if (ch == EOF && ferror(stdin)) {
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