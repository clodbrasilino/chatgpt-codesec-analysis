#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1, got <no output>
  *  test case 1 failed: expected 4, got <no output>
  *  test case 0 failed: expected 1, got <no output>
  */

int findFirstDigit(long num) {
    if (num < 0) num = -num;
    /* Possible weaknesses found:
     * UBSan: -inf is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000000,time:931,execs:419,op:havoc,rep:6)
     */
    int digits = (int)log10(num);
    /* Possible weaknesses found:
     * UBSan: nan is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000000,time:931,execs:419,op:havoc,rep:6)
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