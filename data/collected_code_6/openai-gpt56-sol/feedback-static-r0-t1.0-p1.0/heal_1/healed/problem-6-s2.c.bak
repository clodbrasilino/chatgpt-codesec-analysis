#include <stdbool.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static bool differ_by_one_bit(uint64_t first, uint64_t second)
{
    const uint64_t difference = first ^ second;

    return difference != UINT64_C(0) &&
           (difference & (difference - UINT64_C(1))) == UINT64_C(0);
}

int main(void)
{
    uint64_t first = UINT64_C(0);
    uint64_t second = UINT64_C(0);

    if (scanf("%" SCNu64 " %" SCNu64, &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    puts(differ_by_one_bit(first, second) ? "Yes" : "No");

    return 0;
}