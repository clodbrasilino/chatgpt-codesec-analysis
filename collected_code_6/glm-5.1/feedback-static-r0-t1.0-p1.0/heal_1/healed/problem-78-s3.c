#include <stdio.h>
#include <stdlib.h>

int count_odd_set_bits(int lower, int upper) {
    if (lower > upper) {
        return 0;
    }

    int count = 0;
    for (int i = lower; i <= upper; i++) {
        int n = i;
        int set_bits = 0;
        while (n) {
            set_bits ^= (n & 1);
            n >>= 1;
        }
        if (set_bits) {
            count++;
        }
    }
    return count;
}

int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lower> <upper>\n", argv[0]);
        return 1;
    }

    long lower_long = strtol(argv[1], NULL, 10);
    long upper_long = strtol(argv[2], NULL, 10);

    if (lower_long > 2147483647 || upper_long > 2147483647 || lower_long < -2147483648 || upper_long < -2147483648) {
        fprintf(stderr, "Integer out of range\n");
        return 1;
    }

    int lower = (int)lower_long;
    int upper = (int)upper_long;

    int result = count_odd_set_bits(lower, upper);
    printf("%d\n", result);

    return 0;
}