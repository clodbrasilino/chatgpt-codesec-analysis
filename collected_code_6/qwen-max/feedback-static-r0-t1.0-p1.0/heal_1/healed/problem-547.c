#include <stdio.h>
#include <stdint.h>

int hammingDistance(uint32_t x, uint32_t y) {
    x = x ^ y;
    int distance = 0;
    while (x) {
        distance += x & 1;
        x >>= 1;
    }
    return distance;
}

uint64_t sumOfHammingDistances(uint32_t n) {
    uint64_t totalSum = 0;
    for (uint32_t i = 0; i < n; ++i) {
        totalSum += hammingDistance(i, i + 1);
    }
    return totalSum;
}

int main() {
    uint32_t n;
    printf("Enter a number: ");
    scanf("%u", &n);
    uint64_t result = sumOfHammingDistances(n);
    printf("Sum of Hamming distances: %llu\n", (unsigned long long)result);
    return 0;
}