#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long sum_fourth_power_even(int n) {
    unsigned long long sum = 0;
    unsigned long long even_num = 2;

    for (int i = 0; i < n; i++) {
        unsigned long long squared = even_num * even_num;
        sum += squared * squared;
        even_num += 2;
    }

    return sum;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);

    if (endptr == argv[1] || *endptr != '\0' || errno == ERANGE || val <= 0 || val > INT_MAX) {
        fprintf(stderr, "n must be a positive integer within valid range\n");
        return 1;
    }

    int n = (int)val;
    unsigned long long result = sum_fourth_power_even(n);
    printf("%llu\n", result);

    return 0;
}