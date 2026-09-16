#include <stdio.h>
#include <math.h>

long long count_digits_in_factorial(int n) {
    if (n < 0) {
        return 0; 
    }
    if (n == 0 || n == 1) {
        return 1;
    }

    double digits = 0.0;
    for (int i = 2; i <= n; i++) {
        digits += log10((double)i);
    }

    return (long long)floor(digits) + 1;
}

int main(void) {
    int num;
    
    if (scanf("%d", &num) != 1) {
        return 1;
    }

    if (num < 0) {
        return 1;
    }

    long long result = count_digits_in_factorial(num);
    printf("%lld\n", result);

    return 0;
}