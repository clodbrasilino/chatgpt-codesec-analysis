#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long count_unset_bits_up_to_n(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    unsigned long long count = 0;
    int num_bits = sizeof(n) * 8;
    for (int i = 0; i < num_bits; i++) {
        unsigned long long m = 1ULL << i;
        unsigned long long next_power = m << 1;
        unsigned long long full_cycles = (n + 1) / next_power;
        unsigned long long remainder = (n + 1) % next_power;
        count += full_cycles * m + (remainder > m ? remainder - m : 0);
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
    unsigned long long result = count_unset_bits_up_to_n(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}