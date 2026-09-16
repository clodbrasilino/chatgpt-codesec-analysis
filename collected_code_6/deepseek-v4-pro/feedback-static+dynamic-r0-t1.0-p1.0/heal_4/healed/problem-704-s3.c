#include <stdio.h>
#include <stdlib.h>

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
    char buffer[256];
    
    printf("Enter n: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (sscanf(buffer, "%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (n <= 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    printf("%.15f\n", harmonic_sum(n));
    
    return 0;
}