#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool is_factorial_divisible(uint64_t n, uint64_t x) {
    uint64_t factorial = 1;
    uint64_t i;
    
    for (i = 1; i <= n; i++) {
        factorial *= i;
        if (factorial % x == 0) {
            return true;
        }
    }
    
    return false;
}

uint64_t find_first_natural_number(uint64_t x) {
    uint64_t n = 1;
    
    while (1) {
        if (is_factorial_divisible(n, x)) {
            return n;
        }
        n++;
    }
}

int main() {
    uint64_t x;
    
    printf("Enter the value of x: ");
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long *' but the argument type is 'unsigned long *'. [invalidScanfArgType_int]
     */
    scanf("%llu", &x);
    
    uint64_t result = find_first_natural_number(x);
    
    /* Possible weaknesses found:
     *  %llu in format string (no. 2) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     *  %llu in format string (no. 1) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("The first natural number whose factorial is divisible by %llu is %llu.\n", x, result);
    
    return 0;
}