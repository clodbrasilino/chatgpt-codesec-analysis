#include <stdio.h>
#include <stdint.h>

uint64_t sum_of_fifth_power_of_odds(uint32_t n) {
    uint64_t sum = 0;
    uint32_t current_odd = 1;
    for (uint32_t i = 0; i < n; ++i) {
        uint64_t power = (uint64_t)current_odd * current_odd * current_odd * current_odd * current_odd;
        sum += power;
        current_odd += 2;
    }
    return sum;
}

int main() {
    uint32_t n;
    scanf("%u", &n);
    uint64_t result = sum_of_fifth_power_of_odds(n);
    printf("%llu\n", (unsigned long long)result);
    return 0;
}