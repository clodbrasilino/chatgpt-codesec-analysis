#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double harmonic_sum(int n) {
    if (n <= 0) {
        return 0.0;
    }
    
    if (n < 10000) {
        double sum = 0.0;
        for (int i = 1; i <= n; i++) {
            sum += 1.0 / i;
        }
        return sum;
    } else {
        const double gamma = 0.577215664901532860606512090082402431;
        double n_d = (double)n;
        return log(n_d) + gamma + 1.0 / (2.0 * n_d) - 1.0 / (12.0 * n_d * n_d) + 1.0 / (120.0 * n_d * n_d * n_d * n_d);
    }
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    
    if (endptr == argv[1] || *endptr != '\0' || val <= 0 || val > 1000000000) {
        fprintf(stderr, "Error: n must be a positive integer\n");
        return EXIT_FAILURE;
    }
    
    int n = (int)val;
    double result = harmonic_sum(n);
    printf("%.15f\n", result);
    
    return EXIT_SUCCESS;
}