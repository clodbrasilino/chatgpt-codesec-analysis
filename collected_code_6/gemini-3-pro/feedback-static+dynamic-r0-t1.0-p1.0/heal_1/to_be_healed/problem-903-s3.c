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
        /* Possible weaknesses found:
         * UBSan: shift exponent 64 is too large for 64-bit type 'unsigned long long' (AFL crash: id:000000,sig:06,src:000001,time:7614,execs:325,op:havoc,rep:2)
         */
        unsigned long long blockSize = 1ULL << (i + 1);
        unsigned long long fullBlocks = (n + 1) / blockSize;
        unsigned long long remainder = (n + 1) % blockSize;

        totalSetBits += fullBlocks * (blockSize / 2);
        if (remainder > blockSize / 2) {
            totalSetBits += remainder - (blockSize / 2);
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