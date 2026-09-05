#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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

    char *endptr1;
    errno = 0;
    long lower_long = strtol(argv[1], &endptr1, 10);
    if (errno != 0 || *endptr1 != '\0' || lower_long < INT_MIN || lower_long > INT_MAX) {
        fprintf(stderr, "Integer out of range\n");
        return 1;
    }

    char *endptr2;
    errno = 0;
    long upper_long = strtol(argv[2], &endptr2, 10);
    if (errno != 0 || *endptr2 != '\0' || upper_long < INT_MIN || upper_long > INT_MAX) {
        fprintf(stderr, "Integer out of range\n");
        return 1;
    }

    int lower = (int)lower_long;
    int upper = (int)upper_long;

    int result = count_odd_set_bits(lower, upper);
    printf("%d\n", result);

    return 0;
}