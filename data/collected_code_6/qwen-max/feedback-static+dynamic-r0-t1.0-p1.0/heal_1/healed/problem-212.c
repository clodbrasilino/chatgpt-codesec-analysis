#include <stdio.h>
#include <stdint.h>

uint64_t sum_of_fourth_powers(uint32_t n) {
    uint64_t sum = 0;
    for (uint32_t i = 1; i <= n; ++i) {
        sum += (uint64_t)i * i * i * i;
    }
    return sum;
}

int main() {
    uint32_t n;
    printf("Enter a natural number: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (n == 0) {
        fprintf(stderr, "Input must be a natural number (non-zero)\n");
        return 1;
    }
    uint64_t result = sum_of_fourth_powers(n);
    printf("The sum of the fourth powers of the first %u natural numbers is: %llu\n", n, (unsigned long long)result);
    return 0;
}