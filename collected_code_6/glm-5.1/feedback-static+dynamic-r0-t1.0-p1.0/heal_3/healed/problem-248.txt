#include <stdio.h>
#include <stdlib.h>

double harmonic_sum(unsigned int n) {
    double sum = 0.0;
    for (unsigned int i = n; i >= 1; i--) {
        sum += 1.0 / i;
    }
    return sum;
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    char *endptr;
    unsigned long val = strtoul(argv[1], &endptr, 10);

    if (*endptr != '\0' || val == 0) {
        return EXIT_FAILURE;
    }

    double result = harmonic_sum((unsigned int)val);
    printf("%.15f\n", result);

    return EXIT_SUCCESS;
}