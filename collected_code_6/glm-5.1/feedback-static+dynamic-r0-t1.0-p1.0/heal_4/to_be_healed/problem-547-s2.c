#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_hamming_distances(unsigned long long n) {
    if (n == 0) {
        return 0;
    }

    unsigned long long total = 0;
    unsigned long long i = 1;

    while (i <= n) {
        unsigned long long period = i << 1;
        unsigned long long full_cycles = (n + 1) / period;
        unsigned long long remainder = (n + 1) % period;

        unsigned long long ones = full_cycles * i;
        if (remainder > i) {
            ones += remainder - i;
        }

        unsigned long long zeros = (n + 1) - ones;
        total += ones * zeros;
        i <<= 1;
    }

    return total;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2 || argv[1][0] == '\0') {
        return 1;
    }

    char *endptr;
    unsigned long long n = strtoull(argv[1], &endptr, 10);

    if (*endptr != '\0') {
        return 1;
    }

    unsigned long long result = sum_hamming_distances(n);
    printf("%llu\n", result);

    return 0;
}