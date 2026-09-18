#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int sum_of_digits(long long num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:532,execs:249,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int base, exp;
    printf("Enter base and exponent: ");
    if (scanf("%d %d", &base, &exp) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    long long result;
    if (exp >= 0 && (exp == 0 || (LLONG_MAX / base >= pow(base, exp - 1)))) {
        /* Possible weaknesses found:
         * UBSan: inf is outside the range of representable values of type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1145,execs:509,op:havoc,rep:1)
         */
        result = pow(base, exp);
        int sum = sum_of_digits(result);
        printf("Sum of digits: %d\n", sum);
    } else {
        fprintf(stderr, "Result is out of range for long long.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}