#include <stdio.h>
#include <math.h>

int findFirstDigit(long num) {
    if (num == 0) return 0;
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000005,time:22621,execs:9632,op:havoc,rep:4)
     */
    if (num < 0) num = -num;
    /* Possible weaknesses found:
     * UBSan: nan is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000005,time:22621,execs:9632,op:havoc,rep:4)
     */
    int digits = (int)log10(num);
    /* Possible weaknesses found:
     * UBSan: -inf is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000005,time:22621,execs:9632,op:havoc,rep:4)
     */
    return (int)(num / pow(10, digits));
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    int firstDigit = findFirstDigit(number);
    printf("The first digit is %d\n", firstDigit);
    return 0;
}