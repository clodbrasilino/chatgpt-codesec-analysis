#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool all_bits_unset_in_range(unsigned int num, unsigned int l, unsigned int r) {
    if (l > r || r >= sizeof(num) * CHAR_BIT) {
        return false;
    }
    unsigned int mask_length = r - l + 1;
    unsigned int mask = (mask_length == sizeof(num) * CHAR_BIT) ? ~0U : ((1U << mask_length) - 1);
    mask <<= l;
    return (num & mask) == 0;
}

int main(void) {
    unsigned int num = 0;
    unsigned int l = 0;
    unsigned int r = 0;

    if (scanf("%u %u %u", &num, &l, &r) == 3) {
        if (all_bits_unset_in_range(num, l, r)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }

    return 0;
}