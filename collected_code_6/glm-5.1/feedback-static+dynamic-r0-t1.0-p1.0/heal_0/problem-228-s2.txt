#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool all_bits_unset_in_range(unsigned int num, unsigned int l, unsigned int r) {
    if (l > r || l >= sizeof(unsigned int) * CHAR_BIT || r >= sizeof(unsigned int) * CHAR_BIT) {
        return false;
    }

    unsigned int range_length = r - l + 1;
    if (range_length > sizeof(unsigned int) * CHAR_BIT) {
        return false;
    }

    unsigned int mask = ((1U << range_length) - 1) << l;
    
    return (num & mask) == 0;
}

int main() {
    unsigned int num = 0x50;
    unsigned int l = 1;
    unsigned int r = 3;

    bool result = all_bits_unset_in_range(num, l, r);
    printf("%d\n", result);

    return 0;
}