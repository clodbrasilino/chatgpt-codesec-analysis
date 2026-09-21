#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static bool has_even_parity(uint64_t value)
{
    bool parity = false;

    while (value != UINT64_C(0)) {
        parity = !parity;
        value &= value - UINT64_C(1);
    }

    return !parity;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char extra;
    uint64_t value;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    errno = 0;
    if (sscanf(buffer, " %" SCNu64 " %c", &value, &extra) != 1 || errno != 0) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    puts(has_even_parity(value) ? "Even parity" : "Odd parity");
    return 0;
}