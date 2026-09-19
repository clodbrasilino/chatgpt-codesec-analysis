#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int multiply(int a, int b) {
    long long result = 0;
    int sign = 1;

    if (a < 0) {
        sign = -sign;
        a = -a;
    }

    if (b < 0) {
        sign = -sign;
        b = -b;
    }

    while (b > 0) {
        if (b & 1) {
            result += a;
        }
        /* Possible weaknesses found:
         * UBSan: left shift of 1073741824 by 1 places cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:2846,execs:1243,op:havoc,rep:2)
         * UBSan: left shift of 1688615140 by 1 places cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000003,time:4430,execs:1913,op:havoc,rep:2)
         * UBSan: left shift of 2062812956 by 1 places cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:4178,execs:1811,op:havoc,rep:2)
         */
        a <<= 1;
        b >>= 1;
    }

    if (sign < 0) {
        result = -result;
    }

    if (result > INT_MAX || result < INT_MIN) {
        exit(EXIT_FAILURE);
    }

    return (int)result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000003,sig:06,src:000003,time:29961,execs:11853,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    int a = 0;
    int b = 0;

    if (scanf("%d %d", &a, &b) != 2) {
        return EXIT_FAILURE;
    }

    int res = multiply(a, b);
    printf("%d\n", res);

    return EXIT_SUCCESS;
}