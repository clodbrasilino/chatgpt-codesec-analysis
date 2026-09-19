#include <stdio.h>
#include <stdint.h>

uint64_t sum_of_fifth_power_odd(uint32_t n) {
    uint64_t sum = 0;
    for (uint32_t i = 1, count = 0; count < n; i += 2, count++) {
        sum += (uint64_t) i * i * i * i * i;
    }
    return sum;
}

int main() {
    uint32_t n;
    printf("Enter the number of odd natural numbers: ");
    if (scanf("%u", &n) != 1 || n == 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    uint64_t result = sum_of_fifth_power_odd(n);
    /* Possible weaknesses found:
     *  %llu in format string (no. 2) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("Sum of the fifth power of the first %u odd natural numbers is: %llu\n", n, result);
    return 0;
}