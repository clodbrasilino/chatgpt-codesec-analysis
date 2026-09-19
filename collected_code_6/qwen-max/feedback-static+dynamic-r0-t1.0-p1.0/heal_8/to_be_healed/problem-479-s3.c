#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

int findFirstDigit(long num) {
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000007,time:8314,execs:7158,op:havoc,rep:1)
     */
    if (num < 0) num = labs(num);
    if (num == 0) return 0;
    if (num == LONG_MAX) return 9;

    int digits = 0;
    long n = num;
    while (n >= 10) {
        n /= 10;
        digits++;
    }
    long first_digit = num / (long)powl(10.0L, digits);
    return (int)first_digit;
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    int firstDigit = findFirstDigit(number);
    printf("The first digit is %d\n", firstDigit);
    return 0;
}