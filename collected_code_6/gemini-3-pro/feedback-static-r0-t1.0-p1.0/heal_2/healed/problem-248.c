#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

double harmonic_sum_n_minus_one(int n) {
    if (n <= 1) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 1; i < n; i++) {
        sum += 1.0 / (double)i;
    }

    return sum;
}

int main(int argc, const char *argv[]) {
    int n = 5;
    
    if (argc > 1) {
        char *endptr;
        errno = 0;
        long val = strtol(argv[1], &endptr, 10);
        
        if (errno == 0 && endptr != argv[1] && *endptr == '\0') {
            if (val >= INT_MIN && val <= INT_MAX) {
                n = (int)val;
            } else {
                fprintf(stderr, "Error: Input out of integer range.\n");
                return EXIT_FAILURE;
            }
        } else {
            fprintf(stderr, "Error: Invalid input.\n");
            return EXIT_FAILURE;
        }
    }

    if (n > 1) {
        double result = harmonic_sum_n_minus_one(n);
        printf("%.6f\n", result);
    } else {
        printf("0.000000\n");
    }

    return EXIT_SUCCESS;
}