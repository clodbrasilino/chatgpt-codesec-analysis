#include <stdio.h>
#include <stdint.h>

uint64_t sum_of_fifth_power(int n) {
    uint64_t sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += (uint64_t)i * i * i * i * i;
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    uint64_t result = sum_of_fifth_power(n);
    printf("The sum of the fifth power of the first %d natural numbers is: %llu\n", n, result);
    return 0;
}