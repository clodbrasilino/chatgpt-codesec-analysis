#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long power(int base, int exponent) {
    long long result = 1;
    for(int i = 0; i < exponent; i++) {
        result *= base;
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
    int base, exponent;
    printf("Enter base: ");
    scanf("%d", &base);
    printf("Enter exponent: ");
    scanf("%d", &exponent);

    long long pow = power(base, exponent);
    int sum = sumOfDigits(pow);

    printf("Sum of digits: %d\n", sum);

    return 0;
}