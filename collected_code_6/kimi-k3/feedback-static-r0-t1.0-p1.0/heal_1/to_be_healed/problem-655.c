#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>

static uint64_t sum_fifth_powers(uint32_t n) {
    uint64_t sum = 0;
    uint32_t i;
    for (i = 1; i <= n; i++) {
        uint64_t base = i;
        uint64_t fifth = base * base * base * base * base;
        if (UINT64_MAX - sum < fifth) {
            return UINT64_MAX;
        }
        sum += fifth;
    }
    return sum;
}

int main(void) {
    uint32_t n;
    printf("Enter n: ");
    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu32, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    uint64_t result = sum_fifth_powers(n);
    if (result == UINT64_MAX) {
        fprintf(stderr, "Overflow occurred\n");
        return 1;
    }
    printf("Sum: %" PRIu64 "\n", result);
    return 0;
}