#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

int findFirstDigit(long num) {
    if (num == 0) return 0;
    if (num == LONG_MAX) return 9;

    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000010,time:3968,execs:4046,op:havoc,rep:2)
     */
    unsigned long unum = labs(num);
    int digits = 0;
    unsigned long n = unum;
    while (n >= 10) {
        n /= 10;
        digits++;
    }
    unsigned long first_digit = unum / (unsigned long)powl(10.0L, digits);
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