#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool are_all_bits_in_range(unsigned long long value, unsigned int low, unsigned int high) {
    if (low > high) {
        return false;
    }
    if (high >= (sizeof(unsigned long long) * CHAR_BIT)) {
        return false;
    }
    if (value == 0) {
        return true;
    }
    unsigned long long mask = 0;
    if (high == (sizeof(unsigned long long) * CHAR_BIT - 1)) {
        mask = ~mask;
    } else {
        mask = (1ULL << (high + 1)) - 1;
    }
    unsigned long long lower_mask = (1ULL << low) - 1;
    unsigned long long valid_bits_mask = mask ^ lower_mask;
    return (value & valid_bits_mask) == value;
}

int main(void) {
    unsigned long long val1 = 0x1C;
    unsigned int lo1 = 2, hi1 = 4;
    bool res1 = are_all_bits_in_range(val1, lo1, hi1);
    printf("%d\n", res1);

    unsigned long long val2 = 0x1C;
    unsigned int lo2 = 1, hi2 = 5;
    bool res2 = are_all_bits_in_range(val2, lo2, hi2);
    printf("%d\n", res2);

    unsigned long long val3 = 0;
    unsigned int lo3 = 0, hi3 = 63;
    bool res3 = are_all_bits_in_range(val3, lo3, hi3);
    printf("%d\n", res3);

    unsigned long long val4 = 0x8000000000000000ULL;
    unsigned int lo4 = 63, hi4 = 63;
    bool res4 = are_all_bits_in_range(val4, lo4, hi4);
    printf("%d\n", res4);

    unsigned long long val5 = 0x3;
    unsigned int lo5 = 5, hi5 = 2;
    bool res5 = are_all_bits_in_range(val5, lo5, hi5);
    printf("%d\n", res5);

    return 0;
}