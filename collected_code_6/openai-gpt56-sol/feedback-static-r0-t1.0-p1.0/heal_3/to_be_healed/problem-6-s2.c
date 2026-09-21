#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

static bool differ_by_one_bit(uint64_t first, uint64_t second)
{
    const uint64_t difference = first ^ second;

    return difference != UINT64_C(0) &&
           (difference & (difference - UINT64_C(1))) == UINT64_C(0);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    uint64_t first;
    uint64_t second;
    char extra;

    if (fgets(input, sizeof input, stdin) == NULL ||
        sscanf(input, "%" SCNu64 " %" SCNu64 " %c",
               &first, &second, &extra) != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    puts(differ_by_one_bit(first, second) ? "Yes" : "No");

    return 0;
}