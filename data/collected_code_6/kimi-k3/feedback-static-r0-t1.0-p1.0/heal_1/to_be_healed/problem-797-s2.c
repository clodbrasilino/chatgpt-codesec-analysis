#include <stdio.h>
#include <stdint.h>

uint64_t sum_odd_natural_numbers(uint64_t l, uint64_t r) {
    if (l > r) {
        return 0;
    }
    
    uint64_t first_odd = (l % 2 == 0) ? l + 1 : l;
    
    if (first_odd > r) {
        return 0;
    }
    
    uint64_t last_odd = (r % 2 == 0) ? r - 1 : r;
    uint64_t count = (last_odd - first_odd) / 2 + 1;
    
    return count * (first_odd + last_odd) / 2;
}

int main(void) {
    uint64_t l, r;
    
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long *' but the argument type is 'unsigned long *'. [invalidScanfArgType_int]
     *  %llu in format string (no. 2) requires 'unsigned long long *' but the argument type is 'unsigned long *'. [invalidScanfArgType_int]
     */
    if (scanf("%llu %llu", &l, &r) != 2) {
        return 1;
    }
    
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("%llu\n", sum_odd_natural_numbers(l, r));
    
    return 0;
}