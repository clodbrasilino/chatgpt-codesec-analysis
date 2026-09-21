#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static unsigned int hamming_distance(uint32_t first, uint32_t second)
{
    uint32_t difference = first ^ second;
    unsigned int distance = 0U;

    while (difference != UINT32_C(0)) {
        difference &= difference - UINT32_C(1);
        ++distance;
    }

    return distance;
}

int main(void)
{
    uint32_t first;
    uint32_t second;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu32 " %" SCNu32, &first, &second) != 2) {
        (void)fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (printf("%u\n", hamming_distance(first, second)) < 0) {
        return 1;
    }

    return 0;
}