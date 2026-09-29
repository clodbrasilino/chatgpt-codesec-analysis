#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return 1;
    }

    size_t len = strnlen(argv[1], 21);
    if (len == 0 || len > 20) {
        return 1;
    }

    for (size_t i = 0; i < len; i++) {
        if (argv[1][i] < '0' || argv[1][i] > '9') {
            return 1;
        }
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