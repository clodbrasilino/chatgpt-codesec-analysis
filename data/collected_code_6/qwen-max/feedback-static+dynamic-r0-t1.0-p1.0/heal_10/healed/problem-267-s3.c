#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t sum_of_squares(uint64_t n) {
    uint64_t sum = 0;
    for (uint64_t i = 1; i <= 2 * n - 1; i += 2) {
        sum += i * i;
    }
    return sum;
}

int main() {
    uint64_t n;
    printf("Enter the value of n: ");
    if (scanf("%" SCNu64, &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    uint64_t result = sum_of_squares(n);
    printf("The sum of squares of the first %" PRIu64 " odd natural numbers is: %" PRIu64 "\n", n, result);
    return 0;
}