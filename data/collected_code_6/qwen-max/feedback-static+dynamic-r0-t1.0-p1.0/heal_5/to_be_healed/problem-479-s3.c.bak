#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 4, got 0
  */

int findFirstDigit(long num) {
    if (num == 0) return 0;
    if (num < 0) num = labs(num);
    if (num > 0 && num < LONG_MAX) {
        int digits = (int)(log10(num) + 0.5);
        return (int)(num / pow(10, digits));
    }
    return -1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000005,time:20269,execs:8263,op:havoc,rep:12; likely memory-safety defect
  */

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