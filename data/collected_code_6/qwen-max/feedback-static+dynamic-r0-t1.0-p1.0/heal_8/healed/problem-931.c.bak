#include <stdio.h>
#include <stdint.h>

uint64_t sum_of_cubes(uint64_t n) {
    uint64_t a = n * (n + 1) / 2;
    return a * a;
}

int main() {
    int64_t n;
    printf("Enter a positive integer: ");
    if (scanf("%lld", &n) != 1 || n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    uint64_t result = sum_of_cubes((uint64_t)n);
    printf("The sum of the cubes of the first %lld natural numbers is: %llu\n", n, (unsigned long long)result);
    return 0;
}