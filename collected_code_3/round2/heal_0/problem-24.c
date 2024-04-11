#include <stdio.h>
#include <math.h>

int binaryToDecimal(long long n) {
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0) {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}

int main() {
    long long n;
    printf("Enter a binary number: ");
    scanf("%lld", &n);
    printf("Decimal of binary number %lld is: %d", n, binaryToDecimal(n));
    return 0;
}