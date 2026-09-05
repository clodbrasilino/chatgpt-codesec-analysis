#include <stdio.h>

double harmonic_sum(int n) {
    double sum = 0.0;
    int i;
    
    if (n < 1) {
        return 0.0;
    }
    
    for (i = 1; i < n; i++) {
        sum += 1.0 / i;
    }
    
    return sum;
}

int main(void) {
    int n;
    double result;
    
    printf("Enter n: ");
    
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n < 1) {
        fprintf(stderr, "n must be at least 1\n");
        return 1;
    }
    
    result = harmonic_sum(n);
    printf("Harmonic sum of %d: %.10f\n", n - 1, result);
    
    return 0;
}