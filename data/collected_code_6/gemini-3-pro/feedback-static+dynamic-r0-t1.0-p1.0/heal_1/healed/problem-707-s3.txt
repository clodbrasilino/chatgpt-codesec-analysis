#include <stdio.h>
#include <stdlib.h>

unsigned long long countSetBitsUtil(unsigned long long n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    unsigned long long x = 0;
    unsigned long long temp = n;
    while (temp > 1) {
        x++;
        temp >>= 1;
    }

    unsigned long long bits_up_to_pow2 = x * (1ULL << (x - 1));
    unsigned long long msb_from_pow2_to_n = n - (1ULL << x) + 1;
    unsigned long long remaining_bits = countSetBitsUtil(n - (1ULL << x));

    return bits_up_to_pow2 + msb_from_pow2_to_n + remaining_bits;
}

unsigned long long countSetBits(unsigned long long n) {
    return countSetBitsUtil(n);
}

int main(void) {
    unsigned long long n;

    if (scanf("%llu", &n) != 1) {
        return EXIT_FAILURE;
    }

    unsigned long long result = countSetBits(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}