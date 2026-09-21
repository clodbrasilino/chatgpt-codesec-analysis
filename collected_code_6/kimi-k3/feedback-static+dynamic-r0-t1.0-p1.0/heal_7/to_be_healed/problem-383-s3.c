#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

uint32_t toggle_odd_bits(uint32_t num)
{
    return num ^ UINT32_C(0xAAAAAAAA);
}

int main(void)
{
    uint32_t num;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    unsigned long value;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return 1;
    }

    errno = 0;
    value = strtoul(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || value > UINT32_MAX) {
        return 1;
    }

    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' ||
           *endptr == '\r' || *endptr == '\v' || *endptr == '\f') {
        endptr++;
    }

    if (*endptr != '\0') {
        return 1;
    }

    num = (uint32_t)value;

    printf("%" PRIu32 "\n", toggle_odd_bits(num));

    return 0;
}