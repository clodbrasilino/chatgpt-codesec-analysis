#include <stdio.h>
#include <stdint.h>

uint32_t hammingWeight(uint32_t n) {
    uint32_t count = 0;
    while (n) {
        n &= n - 1;
        count++;
    }
    return count;
}

uint32_t calculateHammingDistance(uint32_t a, uint32_t b) {
    return hammingWeight(a ^ b);
}

uint64_t sumOfConsecutiveHammingDistances(uint32_t n) {
    uint64_t sum = 0;
    for (uint32_t i = 0; i < n; ++i) {
        sum += calculateHammingDistance(i, i + 1);
    }
    return sum;
}

int main() {
    uint32_t n = 15;
    uint64_t result = sumOfConsecutiveHammingDistances(n);
    printf("Sum of Hamming distances from 0 to %u: %llu\n", n, result);
    return 0;
}