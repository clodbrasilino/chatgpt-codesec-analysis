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
         * UBSan: left shift of 1821689629 by 1 places cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:825,execs:326,op:havoc,rep:2)
         * UBSan: left shift of 1228654364 by 1 places cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:484,execs:164,op:havoc,rep:1)
         * UBSan: left shift of 1342177280 by 1 places cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000002,time:1575,execs:662,op:havoc,rep:1)
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