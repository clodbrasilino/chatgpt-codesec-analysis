#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

double harmonic_sum(int n) {
    if (n < 1) {
        return 0.0;
    }
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || val < 1) {
        return EXIT_FAILURE;
    }
    int n = (int)val;
    double result = harmonic_sum(n);
    printf("%.15f\n", result);
    return EXIT_SUCCESS;
}