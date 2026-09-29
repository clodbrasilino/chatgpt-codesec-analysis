#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

void addAndPrintDigits(long a, long b) {
    if (a > 0 && b > LONG_MAX - a) {
        printf("Sum: Overflow, Number of Digits: N/A\n");
        return;
    }
    if (a < 0 && b < LONG_MIN - a) {
        printf("Sum: Underflow, Number of Digits: N/A\n");
        return;
    }
    long sum = a + b;
    /* Possible weaknesses found:
     * UBSan: negation of -9223372036854775808 cannot be represented in type 'long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000006,time:3714,execs:3520,op:havoc,rep:16)
     * UBSan: nan is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000006,time:3714,execs:3520,op:havoc,rep:16)
     */
    int digits = (sum == 0) ? 1 : (int) log10(labs(sum)) + 1;
    printf("Sum: %ld, Number of Digits: %d\n", sum, digits);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000009,time:18592,execs:16495,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    long num1, num2;

    printf("Enter first number: ");
    if (scanf("%ld", &num1) != 1) return 1;

    printf("Enter second number: ");
    if (scanf("%ld", &num2) != 1) return 2;

    addAndPrintDigits(num1, num2);

    return 0;
}