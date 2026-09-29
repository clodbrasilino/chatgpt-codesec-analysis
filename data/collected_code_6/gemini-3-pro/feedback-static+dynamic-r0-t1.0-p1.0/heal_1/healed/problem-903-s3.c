#include <stdio.h>
#include <stdlib.h>

unsigned long long countUnsetBits(unsigned long long n) {
    if (n == 0) {
        return 0;
    }

    unsigned long long totalBits = 0;
    unsigned long long totalSetBits = 0;
    unsigned long long temp = n;
    int bitLength = 0;

    while (temp > 0) {
        bitLength++;
        temp >>= 1;
    }

    for (int i = 0; i < bitLength; i++) {
        unsigned long long fullBlocks = (i == 63) ? 0 : (n >> (i + 1));
        totalSetBits += fullBlocks << i;
        if ((n >> i) & 1) {
            totalSetBits += (n & ((1ULL << i) - 1)) + 1;
        }
    }

    for (unsigned long long i = 1; i <= n; i++) {
        unsigned long long temp_i = i;
        int bits = 0;
        while (temp_i > 0) {
            bits++;
            temp_i >>= 1;
        }
        totalBits += bits;
    }

    return totalBits - totalSetBits;
}

int main(void) {
    unsigned long long n;

    if (scanf("%llu", &n) != 1) {
        return EXIT_FAILURE;
    }

    unsigned long long result = countUnsetBits(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}