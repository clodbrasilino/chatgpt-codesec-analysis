#include <stdio.h>
#include <stdint.h>

uint64_t sum_of_fourth_powers(uint32_t n) {
    uint64_t sum = 0;
    for (uint32_t i = 1; i <= n; ++i) {
        uint32_t odd_number = 2 * i - 1;
        sum += (uint64_t)odd_number * odd_number * odd_number * odd_number;
    }
    return sum;
}

int main(void) {
    uint32_t n = 5;
    uint64_t result = sum_of_fourth_powers(n);
    /* Possible weaknesses found:
     *  %llu in format string (no. 2) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("The sum of the fourth power of the first %u odd natural numbers is: %llu\n", n, result);
    return 0;
}