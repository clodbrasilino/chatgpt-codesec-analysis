#include <stdio.h>
#include <stdint.h>

uint64_t sum_of_fifth_power_of_odds(uint32_t n) {
    uint64_t sum = 0;
    uint32_t current_odd = 1;
    for (uint32_t i = 0; i < n; ++i) {
        sum += (uint64_t)current_odd * current_odd * current_odd * current_odd * current_odd;
        current_odd += 2;
    }
    return sum;
}

int main() {
    uint32_t n;
    scanf("%u", &n);
    uint64_t result = sum_of_fifth_power_of_odds(n);
    /* Possible weaknesses found:
     *  %llu in format string (no. 1) requires 'unsigned long long' but the argument type is 'unsigned long'. [invalidPrintfArgType_uint]
     */
    printf("%llu\n", result);
    return 0;
}