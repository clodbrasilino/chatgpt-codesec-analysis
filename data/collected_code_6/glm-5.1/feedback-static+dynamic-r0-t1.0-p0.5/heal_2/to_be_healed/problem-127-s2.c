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
         * UBSan: left shift of 1983127224 by 1 places cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:987,execs:511,op:havoc,rep:8)
         * UBSan: left shift of 1155947192 by 1 places cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000003,time:2751,execs:1268,op:havoc,rep:6)
         * UBSan: left shift of 1342177280 by 1 places cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:1167,execs:594,op:havoc,rep:4)
         * UBSan: left shift of 1688615140 by 1 places cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000003,time:4291,execs:1825,op:havoc,rep:6)
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
  * Fuzzing found a crash (signal 6) on input id:000004,sig:06,src:000003,time:13227,execs:5637,op:havoc,rep:8; likely memory-safety defect
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