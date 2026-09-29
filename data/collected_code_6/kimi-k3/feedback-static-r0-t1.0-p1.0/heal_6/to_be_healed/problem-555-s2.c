#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>

int64_t compute_difference(int64_t n) {
    if (n < 0) {
        return -1;
    }
    if (n > 18156) {
        return -1;
    }
    int64_t sum = n * (n + 1) / 2;
    int64_t sum_of_cubes = sum * sum;
    return sum_of_cubes - sum;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    int64_t n;
    char *endptr;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    errno = 0;
    n = strtoimax(buffer, &endptr, 10);

    if (errno == ERANGE || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return 1;
    }

    printf("%" PRId64 "\n", compute_difference(n));
    return 0;
}