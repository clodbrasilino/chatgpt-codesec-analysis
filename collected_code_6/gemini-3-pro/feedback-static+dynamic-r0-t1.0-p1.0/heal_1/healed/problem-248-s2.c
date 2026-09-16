#include <stdio.h>
#include <stdlib.h>

double calculate_harmonic_sum_n_minus_one(unsigned int n) {
    if (n <= 1) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (unsigned int i = 1; i < n; ++i) {
        sum += 1.0 / (double)i;
    }
    
    return sum;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long int parsed_value = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || parsed_value < 1) {
        fprintf(stderr, "Error: Invalid input. Please provide a positive integer.\n");
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)parsed_value;
    double result = calculate_harmonic_sum_n_minus_one(n);

    printf("%.6f\n", result);

    return EXIT_SUCCESS;
}