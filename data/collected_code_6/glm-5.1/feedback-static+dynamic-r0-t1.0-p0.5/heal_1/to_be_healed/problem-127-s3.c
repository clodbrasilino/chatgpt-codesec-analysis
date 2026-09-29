#include <stdio.h>
#include <stdlib.h>

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
         * UBSan: left shift of 1073741824 by 1 places cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:928,execs:549,op:havoc,rep:5)
         * UBSan: left shift of 2062812956 by 1 places cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:810,execs:483,op:havoc,rep:1)
         */
        a <<= 1;
        b >>= 1;
    }

    if (sign < 0) {
        result = -result;
    }

    if (result > 2147483647 || result < -2147483648) {
        exit(EXIT_FAILURE);
    }

    return (int)result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000003,time:1900,execs:1077,op:havoc,rep:5; likely memory-safety defect
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