#include <stdio.h>
#include <stdint.h>

uint64_t sum_fourth_power_odd(uint32_t n) {
    uint64_t sum = 0;
    for (uint32_t i = 0; i < n; ++i) {
        uint64_t odd = 2ULL * i + 1;
        uint64_t square = odd * odd;
        sum += square * square;
    }
    return sum;
}

int main(void) {
    uint32_t n;
    printf("Enter n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    uint64_t result = sum_fourth_power_odd(n);
    /* Possible weaknesses found:
     *  %llu in format string (no. 2) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("Sum of fourth powers of first %u odd natural numbers: %llu\n", n, result);
    
    return 0;
}