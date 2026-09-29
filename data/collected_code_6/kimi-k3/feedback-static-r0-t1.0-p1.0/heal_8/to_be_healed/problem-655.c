#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *endptr;
    unsigned long val;

    printf("Enter n: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (strchr(buffer, '\n') == NULL) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    val = strtoul(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0') || val > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    n = (uint32_t)val;

    uint64_t result = sum_fifth_powers(n);
    if (result == UINT64_MAX) {
        fprintf(stderr, "Overflow occurred\n");
        return 1;
    }
    printf("Sum: %" PRIu64 "\n", result);
    return 0;
}