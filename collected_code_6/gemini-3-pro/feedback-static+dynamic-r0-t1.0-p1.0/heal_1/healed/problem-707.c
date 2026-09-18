#include <stdio.h>
#include <stdlib.h>

unsigned long long countSetBits(unsigned int n) {
    if (n == 0) {
        return 0;
    }

    unsigned long long total_bits = 0;
    unsigned int x = n;
    
    while (x > 0) {
        unsigned int p = 0;
        unsigned int temp = x;
        while (temp > 1) {
            temp >>= 1;
            p++;
        }

        if (p == 0) {
            total_bits += 1;
            break;
        }

        total_bits += (1ULL << (p - 1)) * p + (x - (1U << p) + 1);
        x -= (1U << p);
    }
    
    return total_bits;
}

int main(void) {
    unsigned int n;

    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = countSetBits(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}