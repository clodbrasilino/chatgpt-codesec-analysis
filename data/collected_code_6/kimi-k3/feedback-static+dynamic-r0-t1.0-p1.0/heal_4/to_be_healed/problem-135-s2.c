#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

static bool hexagonal_number(uint64_t n, uint64_t *result)
{
    if (n == 0) {
        return false;
    }
    if (n > UINT64_MAX / (2 * n - 1)) {
        return false;
    }
    *result = n * (2 * n - 1);
    return true;
}

int main(void)
{
    uint64_t n;
    uint64_t result;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    unsigned long long temp;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    errno = 0;
    temp = strtoull(buffer, &endptr, 10);
    
    if (errno == ERANGE || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    n = (uint64_t)temp;

    if (!hexagonal_number(n, &result)) {
        fprintf(stderr, "Overflow or invalid input\n");
        return 1;
    }

    printf("%" PRIu64 "\n", result);
    return 0;
}