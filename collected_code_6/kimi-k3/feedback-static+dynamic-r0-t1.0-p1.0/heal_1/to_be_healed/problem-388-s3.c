#include <stdio.h>
#include <stdint.h>
#include <limits.h>

uint64_t highest_power_of_two(uint64_t n) {
    if (n == 0) {
        return 0;
    }
    
    n |= (n >> 1);
    n |= (n >> 2);
    n |= (n >> 4);
    n |= (n >> 8);
    n |= (n >> 16);
    n |= (n >> 32);
    
    return n - (n >> 1);
}

int main(void) {
    uint64_t n;
    
    printf("Enter a positive integer: ");
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long *' but the argument type is 'unsigned long *'. [invalidScanfArgType_int]
     */
    if (scanf("%llu", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    uint64_t result = highest_power_of_two(n);
    /* Possible weaknesses found:
     *  %llu in format string (no. 2) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     *  %llu in format string (no. 1) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("Highest power of 2 <= %llu: %llu\n", n, result);
    
    return 0;
}