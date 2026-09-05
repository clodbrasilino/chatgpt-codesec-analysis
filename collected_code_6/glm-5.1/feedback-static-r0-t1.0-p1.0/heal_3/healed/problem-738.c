#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

double geometric_sum(int n) {
    if (n <= 1) {
        return 1.0;
    }
    double total = 0.0;
    double current = 1.0;
    for (int i = 0; i < n; i++) {
        total += current;
        current /= 2.0;
    }
    return total;
}

int main(int argc, char const * const * argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    double result = geometric_sum((int)val);
    printf("%f\n", result);
    return EXIT_SUCCESS;
}