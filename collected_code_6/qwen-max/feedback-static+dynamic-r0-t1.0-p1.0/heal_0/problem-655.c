#include <stdio.h>
#include <stdint.h>

uint64_t sum_of_fifth_powers(uint32_t n) {
    uint64_t sum = 0;
    for (uint32_t i = 1; i <= n; ++i) {
        sum += (uint64_t)i * i * i * i * i;
    }
    return sum;
}

int main() {
    uint32_t n;
    scanf("%u", &n);
    if (n > 0) {
        uint64_t result = sum_of_fifth_powers(n);
        printf("%lu\n", result);
    } else {
        printf("Input must be a positive integer.\n");
    }
    return 0;
}