#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long countDigitsInFactorial(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0 || n == 1) {
        return 1;
    }
    
    double digits = 0;
    for (int i = 2; i <= n; i++) {
        digits += log10(i);
    }
    
    return (long long)floor(digits) + 1;
}

int main(void) {
    int number;
    
    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    long long result = countDigitsInFactorial(number);
    
    if (result == -1) {
        fprintf(stderr, "Factorial of a negative number is undefined\n");
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", result);
    
    return EXIT_SUCCESS;
}