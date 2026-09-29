#include <stdio.h>

long long int nthDigit(long long int numerator, long long int denominator, int n) {
    long long int result = numerator/denominator;
    long long int nth_num;
    int count = 0;
    while (result != 0) {
        nth_num = result%10;
        result /= 10;
        count++;
        if (count == n) {
            return nth_num;
        }
    }
    return -1;
}

int main() {
    long long int numerator, denominator;
    int n;
    printf("Enter numerator, denominator, and the nth term you want to find:\n");
    if(scanf("%lld %lld %d", &numerator, &denominator, &n)!=3 || denominator==0 || n<=0) {
        fprintf(stderr, "Invalid input. Please make sure to provide non-zero denominator and a positive nth term.\n");
        return -1;
    }
    long long int nth_digit = nthDigit(numerator, denominator, n);
    if(nth_digit == -1) {
        printf("The digit doesn't exist\n");
    }
    else {
        printf("The %dth digit of %lld/%lld is %lld\n", n, numerator, denominator, nth_digit);
    }
    return 0;
}