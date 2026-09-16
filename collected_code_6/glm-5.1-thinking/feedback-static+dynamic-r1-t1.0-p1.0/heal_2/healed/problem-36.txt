#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_nth_digit(int numerator, int denominator, int n) {
    if (denominator <= 0) {
        return -1;
    }
    if (numerator < 0 || numerator >= denominator) {
        return -1;
    }
    if (n <= 0) {
        return -1;
    }

    long long remainder = numerator % denominator;
    int digit = 0;

    for (int i = 0; i < n; i++) {
        remainder *= 10;
        digit = (int)(remainder / denominator);
        remainder = remainder % denominator;
    }

    return digit;
}

int main(int argc, const char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <numerator> <denominator> <n>\n", argv[0]);
        return 1;
    }

    char *endptr;
    long num_val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || endptr == argv[1] || num_val < 0 || num_val > INT_MAX) {
        fprintf(stderr, "Invalid numerator\n");
        return 1;
    }

    long den_val = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || endptr == argv[2] || den_val <= 0 || den_val > INT_MAX) {
        fprintf(stderr, "Invalid denominator\n");
        return 1;
    }

    long n_val = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0' || endptr == argv[3] || n_val <= 0 || n_val > INT_MAX) {
        fprintf(stderr, "Invalid n\n");
        return 1;
    }

    int result = find_nth_digit((int)num_val, (int)den_val, (int)n_val);
    if (result < 0) {
        fprintf(stderr, "Error calculating nth digit\n");
        return 1;
    }

    printf("%d\n", result);
    return 0;
}