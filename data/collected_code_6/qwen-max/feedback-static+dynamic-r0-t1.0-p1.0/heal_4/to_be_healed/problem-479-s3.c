#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

int findFirstDigit(long num) {
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000006,time:5397,execs:5927,op:havoc,rep:1)
     */
    if (num < 0) num = labs(num);
    if (num == 0) return 0;
    if (num == LONG_MAX) return 9;

    /* Possible weaknesses found:
     * UBSan: nan is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000006,time:5397,execs:5927,op:havoc,rep:1)
     */
    int digits = (int)log10l((long double)num);
    /* Possible weaknesses found:
     * UBSan: -inf is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000006,time:5397,execs:5927,op:havoc,rep:1)
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