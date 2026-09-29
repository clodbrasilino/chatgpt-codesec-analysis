#include <stdio.h>
#include <math.h>

int findFirstDigit(long n) {
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000001,sig:06,src:000005,time:38109,execs:15329,op:havoc,rep:3)
     */
    if (n < 0) n = -n;
    /* Possible weaknesses found:
     * UBSan: nan is outside the range of representable values of type 'int' (AFL crash: id:000001,sig:06,src:000005,time:38109,execs:15329,op:havoc,rep:3)
     * UBSan: -inf is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000004,time:25571,execs:10390,op:havoc,rep:1)
     * UBSan: -inf is outside the range of representable values of type 'int' (AFL crash: id:000001,sig:06,src:000005,time:38109,execs:15329,op:havoc,rep:3)
     * UBSan: nan is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000004,time:25571,execs:10390,op:havoc,rep:1)
     */
    return (int)(n / pow(10, (int)log10(n)));
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    if (scanf("%ld", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    int firstDigit = findFirstDigit(number);
    printf("The first digit of %ld is %d.\n", number, firstDigit);
    return 0;
}