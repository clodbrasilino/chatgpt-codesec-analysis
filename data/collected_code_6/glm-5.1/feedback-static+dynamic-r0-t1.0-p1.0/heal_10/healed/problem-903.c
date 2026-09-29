#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long count_unset_bits_up_to(unsigned long long n) {
    unsigned long long count = 0;
    unsigned long long range = n + 1;
    int num_bits = (sizeof(n) * 8) - __builtin_clzll(range | 1);
    for (int i = 0; i < num_bits; i++) {
        unsigned long long next_power = 1ULL << (i + 1);
        unsigned long long full_cycles = range / next_power;
        unsigned long long remainder = range % next_power;
        unsigned long long zeros_in_complete_cycle = full_cycles << i;
        unsigned long long partial_zeros = 0;
        unsigned long long half_power = 1ULL << i;
        if (remainder > half_power) {
            partial_zeros = remainder - half_power;
        }
        count += zeros_in_complete_cycle + partial_zeros;
    }
    return count;
}

int main(int argc, char * const argv[]) {
    unsigned long long n;
    if (argc != 2) {
        if (fscanf(stdin, "%llu", &n) != 1) {
            return EXIT_FAILURE;
        }
    } else {
        char *endptr;
        n = strtoull(argv[1], &endptr, 10);
        if (*endptr != '\0' || n == ULLONG_MAX) {
            return EXIT_FAILURE;
        }
    }
    unsigned long long result = count_unset_bits_up_to(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}