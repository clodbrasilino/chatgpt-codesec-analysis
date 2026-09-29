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
    uint64_t count;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }
            break;
        }

        if (length == UINT64_MAX) {
            return EXIT_FAILURE;
        }

        ++length;
    }

    if (count_non_empty_substrings(length, &count) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}