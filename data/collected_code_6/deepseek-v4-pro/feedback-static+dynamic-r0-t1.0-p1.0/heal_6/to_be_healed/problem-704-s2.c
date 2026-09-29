#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'log'
  */

double harmonic_sum(int n) {
    if (n <= 0) {
        return 0.0;
    }
    
    double sum = 0.0;
    if (n < 10000) {
        for (int i = 1; i <= n; i++) {
            sum += 1.0 / i;
        }
    } else {
        const double gamma = 0.577215664901532860606512090082402431;
        /* Possible weaknesses found:
         *  include the header <math.h> or explicitly provide a declaration for 'log'
         *  implicit declaration of function 'log' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'log' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        sum = log((double)n) + gamma + 1.0 / (2.0 * n) - 1.0 / (12.0 * n * n) + 1.0 / (120.0 * n * n * n * n);
    }
    return sum;
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
    printf("%.10f\n", result);
    
    return EXIT_SUCCESS;
}