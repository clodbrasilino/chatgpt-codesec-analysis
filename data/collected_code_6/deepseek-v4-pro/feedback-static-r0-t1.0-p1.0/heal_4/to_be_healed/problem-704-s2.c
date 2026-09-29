#include <stdio.h>
#include <stdlib.h>

double harmonic_sum(int n) {
    if (n <= 0) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (int i = 1; i < n; i++) {
        sum += 1.0 / i;
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
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
    printf("Harmonic sum H(%d-1) = %.10f\n", n, harmonic_sum(n));
    
    return EXIT_SUCCESS;
}