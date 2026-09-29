#include <stdio.h>
#include <stdlib.h>

double geometric_sum(int n) {
    if (n < 1) {
        return 0.0;
    }
    
    double term = 1.0;
    double sum = 1.0;
    
    for (int i = 1; i < n; i++) {
        term *= 0.5;
        sum += term;
    }
    
    return 2.0 * sum;
}

int main(void) {
    char buffer[256];
    int n;
    
    printf("Enter n: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (sscanf(buffer, "%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 1) {
        fprintf(stderr, "n must be at least 1\n");
        return EXIT_FAILURE;
    }
    
    printf("Geometric sum: %.10f\n", geometric_sum(n));
    return EXIT_SUCCESS;
}