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
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000006,time:46909,execs:19397,op:havoc,rep:1)
     */
    if (num < 0) num = labs(num);
    if (num == LONG_MAX) return 1;
    /* Possible weaknesses found:
     * UBSan: nan is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000006,time:46909,execs:19397,op:havoc,rep:1)
     */
    int digits = (int)(log10((double)num) + 0.5);
    if (digits < 0 || digits > INT_MAX) return 0;
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