#include <stdio.h>
#include <stdlib.h>

unsigned long long count_unset_bits_up_to_n(unsigned long long n) {
    unsigned long long count = 0;
    int i = 0;

    while (1ULL << i <= n) {
        unsigned long long power = 1ULL << i;
        unsigned long long next_power = power * 2;
        unsigned long long remainder = (n + 1) % next_power;

        count += (n + 1) - remainder;
        count += (remainder > power) ? power : remainder;

        i++;
    }

    return count;
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr = NULL;
    unsigned long long n = strtoull(argv[1], &endptr, 10);

    if (*endptr != '\0' || (n == 0 && argv[1][0] != '0')) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("%llu\n", count_unset_bits_up_to_n(n));

    return 0;
}