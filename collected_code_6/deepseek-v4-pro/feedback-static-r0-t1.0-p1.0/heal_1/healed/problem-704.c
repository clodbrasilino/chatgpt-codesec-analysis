#include <stdio.h>
#include <stdlib.h>

double harmonic_sum(int n) {
    if (n <= 0) {
        return 0.0;
    }
    double sum = 0.0;
    for (int i = 2; i <= n; i++) {
        sum += 1.0 / (i - 1);
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Error: Invalid integer\n");
        return EXIT_FAILURE;
    }
    if (val <= 0 || val > 1000000) {
        fprintf(stderr, "Error: n must be between 1 and 1000000\n");
        return EXIT_FAILURE;
    }
    
    int n = (int)val;
    double result = harmonic_sum(n);
    printf("%.10f\n", result);
    
    return EXIT_SUCCESS;
}