#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findDifference(long long n) {
    int sumEven = 0;
    int sumOdd = 0;
    
    if (n < 0) {
        if (n == LLONG_MIN) {
            n = (LLONG_MIN + 1) * -1;
            sumEven += 8; 
        } else {
            n = -n;
        }
    }
    
    if (n == 0) {
        return 0;
    }
    
    while (n > 0) {
        int digit = n % 10;
        if (digit % 2 == 0) {
            sumEven += digit;
        } else {
            sumOdd += digit;
        }
        n /= 10;
    }
    
    return sumEven - sumOdd;
}

int main(void) {
    long long n;
    
    if (scanf("%lld", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    int result = findDifference(n);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}