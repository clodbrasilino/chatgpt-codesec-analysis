#include <stdio.h>
#include <stdlib.h>

double average_of_cubes(unsigned int n) {
    if (n == 0) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (unsigned int i = 1; i <= n; i++) {
        sum += (double)i * (double)i * (double)i;
    }
    
    return sum / n;
}

int main(void) {
    unsigned int n;
    
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    double result = average_of_cubes(n);
    printf("%f\n", result);
    
    return EXIT_SUCCESS;
}