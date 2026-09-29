#include <stdio.h>
#include <math.h>

long long countDigitsInFactorial(int n) {
    if (n < 0) {
        return 0;
    }
    if (n <= 1) {
        return 1;
    }
    
    double digits = 0.0;
    for (int i = 2; i <= n; i++) {
        digits += log10(i);
    }
    
    return (long long)floor(digits) + 1;
}

int main(void) {
    int number;
    
    if (scanf("%d", &number) != 1) {
        return 1;
    }
    
    if (number < 0) {
        return 1;
    }
    
    long long digitCount = countDigitsInFactorial(number);
    printf("%lld\n", digitCount);
    
    return 0;
}