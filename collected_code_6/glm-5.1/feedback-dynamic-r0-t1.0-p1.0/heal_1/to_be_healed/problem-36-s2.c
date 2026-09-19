#include <stdio.h>
#include <stdlib.h>

int find_nth_digit(int numerator, int denominator, int n) {
    if (denominator == 0 || n <= 0) {
        return -1;
    }

    if (numerator < 0) {
        numerator = -numerator;
    }
    if (denominator < 0) {
        denominator = -denominator;
    }

    numerator = numerator % denominator;

    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 481471546 * 10 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000003,time:9048,execs:3626,op:havoc,rep:2)
         * UBSan: signed integer overflow: 1000000000 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:405,execs:225,op:havoc,rep:2)
         */
        numerator *= 10;
        if (numerator == 0 && i > 0) {
            return 0;
        }
    }

    int digit = (numerator / denominator) % 10;

    return digit;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000003,time:8459,execs:3432,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int num, den, n;

    if (scanf("%d %d %d", &num, &den, &n) != 3) {
        return EXIT_FAILURE;
    }

    int result = find_nth_digit(num, den, n);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}