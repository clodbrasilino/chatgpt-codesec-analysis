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
         * UBSan: left shift of 1276409562 by 1 places cannot be represented in type 'int' (AFL crash: id:000004,sig:06,src:000001,time:14139,execs:6185,op:havoc,rep:4)
         * UBSan: left shift of 1316134912 by 1 places cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000001,time:1677,execs:651,op:havoc,rep:1)
         * UBSan: left shift of 1342177280 by 1 places cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1019,execs:437,op:havoc,rep:2)
         * UBSan: left shift of 1773790788 by 1 places cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000001,time:3534,execs:1386,op:havoc,rep:2)
         * UBSan: left shift of 1228654360 by 1 places cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:1341,execs:521,op:havoc,rep:1)
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