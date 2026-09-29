#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int count_tilings(size_t n, uint64_t *result)
{
    uint64_t previous = 1;
    uint64_t current = 1;

    if (result == NULL) {
        return -1;
    }

    for (size_t i = 2; i <= n; ++i) {
        if (UINT64_MAX - current < previous) {
            return -1;
        }

        uint64_t next = current + previous;
        previous = current;
        current = next;
    }

    *result = current;
    return 0;
}

int main(void)
{
    unsigned long long input;
    uint64_t result;

    errno = 0;
    if (scanf("%llu", &input) != 1 || errno != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (input > SIZE_MAX || count_tilings((size_t)input, &result) != 0) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}