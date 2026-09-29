#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

int findFirstDigit(long num) {
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000007,time:2083,execs:2013,op:havoc,rep:7)
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
    /* Possible weaknesses found:
     * UBSan: -9.22337e+18 is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000007,time:2083,execs:2013,op:havoc,rep:7)
     */
    return (int)(num / powl(10.0L, digits));
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    int firstDigit = findFirstDigit(number);
    printf("The first digit is %d\n", firstDigit);
    return 0;
}