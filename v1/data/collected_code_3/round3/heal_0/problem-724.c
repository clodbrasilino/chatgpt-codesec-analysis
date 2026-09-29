#include <stdio.h>
#include <math.h>
#include <stdlib.h>

long long power(int base, int exp) {
    long long result = 1;
    while(exp) {
        if(exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
}

int sumOfDigits(long long num) {
    int sum = 0;
    while(num != 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int main() {
    int base, exp;
    printf("Enter base: ");
    scanf("%d", &base);
    printf("Enter exponent: ");
    scanf("%d", &exp);
    long long pow = power(base, exp);
    printf("Sum of digits: %d\n", sumOfDigits(pow));
    return 0;
}