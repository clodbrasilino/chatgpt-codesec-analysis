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
         * UBSan: left shift of 1422222208 by 1 places cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:1346,execs:623,op:havoc,rep:2)
         * UBSan: left shift of 1923267956 by 1 places cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000003,time:1370,execs:633,op:havoc,rep:8)
         * UBSan: left shift of 2066312932 by 1 places cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000003,time:1471,execs:677,op:havoc,rep:2)
         * UBSan: left shift of 1073741824 by 1 places cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:390,execs:190,op:havoc,rep:1)
         */
        a <<= 1;
        b >>= 1;
    }

    if (sign < 0) {
        result = -result;
    }

    if (result > INT_MAX || result < INT_MIN) {
        abort();
    }

    return (int)result;
}

int main(void) {
    int a, b;

    if (scanf("%d %d", &a, &b) != 2) {
        return EXIT_FAILURE;
    }

    int res = multiply(a, b);
    printf("%d\n", res);

    return EXIT_SUCCESS;
}