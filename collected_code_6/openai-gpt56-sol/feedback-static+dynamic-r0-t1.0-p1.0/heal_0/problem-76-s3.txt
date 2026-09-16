#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

static int count_squares(uint64_t width, uint64_t height, uint64_t *result)
{
    uint64_t smaller = width < height ? width : height;
    uint64_t larger = width < height ? height : width;
    __uint128_t count;

    if (smaller == 0U || result == NULL) {
        return 0;
    }

    count = (__uint128_t)smaller * (smaller + 1U) *
            (3U * larger - smaller + 1U) / 6U;

    if (count > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)count;
    return 1;
}

int main(void)
{
    uint64_t width;
    uint64_t height;
    uint64_t result;

    if (scanf("%" SCNu64 " %" SCNu64, &width, &height) != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!count_squares(width, height, &result)) {
        fputs("Invalid dimensions or result overflow\n", stderr);
        return 1;
    }

    printf("%" PRIu64 "\n", result);
    return 0;
}