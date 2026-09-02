#include <stdio.h>

double harmonic_sum(int n) {
    double sum = 0.0;
    int i;
    
    if (n <= 1) {
        return 0.0;
    }
    
    for (i = 1; i < n; i++) {
        sum += 1.0 / i;
    }
    
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n <= 1) {
        printf("Harmonic sum of %d-1 = 0.000000\n", n);
    } else {
        printf("Harmonic sum of %d-1 = %f\n", n, harmonic_sum(n));
    }
    
    return 0;
}