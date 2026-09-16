#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long sum_of_squares_odd(int n) {
    if (n <= 0) {
        return 0;
    }
    
    if ((unsigned long long)n > ULLONG_MAX / (2ULL * n - 1) / (2ULL * n - 1)) {
        exit(EXIT_FAILURE);
    }

    unsigned long long sum = 0;
    for (int i = 1; i <= n; i++) {
        unsigned long long odd = 2ULL * i - 1;
        sum += odd * odd;
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }

    unsigned long long result = sum_of_squares_odd((int)val);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}