#include <stdio.h>
#include <stdlib.h>

double harmonic_sum(int n) {
    double sum = 0.0;
    int i;
    
    if (n < 1) {
        return 0.0;
    }
    
    for (i = 1; i <= n; i++) {
        sum += 1.0 / i;
    }
    
    return sum;
}

int main(void) {
    int n;
    double result;
    
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    
    if (n < 1) {
        return 1;
    }
    
    result = harmonic_sum(n);
    printf("%.15f\n", result);
    fflush(stdout);
    
    return 0;
}