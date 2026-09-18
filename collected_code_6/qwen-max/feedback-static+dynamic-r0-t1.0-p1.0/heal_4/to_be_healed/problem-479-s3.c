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
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000006,time:32802,execs:13537,op:havoc,rep:2)
     */
    if (num < 0) num = labs(num);
    if (num > 0 && num < LONG_MAX) {
        int digits = (int)(log10(num) + 0.5);
        return (int)(num / pow(10, digits));
    }
    return -1;
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    int firstDigit = findFirstDigit(number);
    if (firstDigit != -1) {
        printf("The first digit is %d\n", firstDigit);
    } else {
        printf("Invalid input\n");
    }
    return 0;
}