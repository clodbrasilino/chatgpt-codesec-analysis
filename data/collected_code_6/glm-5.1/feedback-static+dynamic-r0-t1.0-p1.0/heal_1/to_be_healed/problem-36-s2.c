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
         * UBSan: signed integer overflow: 1000000000 * 10 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:3131,execs:1848,op:havoc,rep:2)
         * UBSan: signed integer overflow: 247248896 * 10 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000007,time:4151,execs:2448,op:havoc,rep:1)
         * UBSan: signed integer overflow: 300000000 * 10 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:104,execs:73,op:havoc,rep:3)
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
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000009,time:3957,execs:2338,op:havoc,rep:3; likely memory-safety defect
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