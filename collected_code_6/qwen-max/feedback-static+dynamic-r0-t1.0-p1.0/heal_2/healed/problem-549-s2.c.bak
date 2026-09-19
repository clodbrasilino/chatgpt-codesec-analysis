#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

uint64_t sum_of_fifth_power_odd(int n) {
    if (n <= 0) return 0;
    uint64_t sum = 0;
    int i = 1;
    for (int count = 0; count < n; i += 2, count++) {
        uint64_t i_64 = (uint64_t)i;
        sum += i_64 * i_64 * i_64 * i_64 * i_64;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter the number of odd natural numbers: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > INT_MAX / 2) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    uint64_t result = sum_of_fifth_power_odd(n);
    printf("Sum of the fifth power of the first %d odd natural numbers is: %llu\n", n, (unsigned long long)result);
    return 0;
}