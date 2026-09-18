#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 0
  */

int findFirstDigit(long num) {
    if (num == 0) return 0;
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000005,time:45568,execs:18776,op:havoc,rep:2)
     */
    if (num < 0) num = labs(num);
    /* Possible weaknesses found:
     * UBSan: nan is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000005,time:45568,execs:18776,op:havoc,rep:2)
     */
    int digits = (int)(log10((double)num) + 0.5);
    /* Possible weaknesses found:
     * UBSan: -inf is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000005,time:45568,execs:18776,op:havoc,rep:2)
     */
    return (int)(num / pow(10, digits));
}

int main() {
    long number;
    printf("Enter a number: ");
    if (scanf("%ld", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    int firstDigit = findFirstDigit(number);
    if (firstDigit >= 0) {
        printf("The first digit is %d\n", firstDigit);
    } else {
        printf("Invalid input\n");
    }
    return 0;
}