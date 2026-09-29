#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

double geometric_sum(int n) {
    if (n <= 0) {
        return 0.0;
    }
    return 2.0 - (1.0 / (1 << (n - 1)));
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    double result = geometric_sum((int)val);
    printf("%.8f\n", result);
    fflush(stdout);
    return EXIT_SUCCESS;
}