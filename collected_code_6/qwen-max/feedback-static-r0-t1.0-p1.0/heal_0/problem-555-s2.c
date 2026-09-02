#include <stdio.h>
#include <stdint.h>

uint64_t sum_of_cubes(uint32_t n) {
    return (n * (n + 1) / 2) * (n * (n + 1) / 2);
}

uint64_t sum_of_naturals(uint32_t n) {
    return n * (n + 1) / 2;
}

uint64_t difference_between_sums(uint32_t n) {
    uint64_t cubes_sum = sum_of_cubes(n);
    uint64_t naturals_sum = sum_of_naturals(n);
    return cubes_sum - naturals_sum;
}

int main() {
    uint32_t n;
    printf("Enter a positive integer: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Input is not a valid positive integer.\n");
        return 1;
    }
    uint64_t result = difference_between_sums(n);
    printf("The difference between the sum of cubes and the sum of the first %u natural numbers is: %llu\n", n, result);
    return 0;
}