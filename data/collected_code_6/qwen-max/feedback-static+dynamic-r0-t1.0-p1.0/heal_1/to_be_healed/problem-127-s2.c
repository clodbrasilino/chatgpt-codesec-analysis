#include <stdio.h>
#include <limits.h>

int multiply(int x, int y) {
    int result = 0;
    int negativeResult = 0;
    if (y < 0) {
        y = -y;
        negativeResult = 1;
    }
    while (y > 0) {
        if (y & 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 883038752 + 1766077504 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:7,execs:15,op:(null),pos:0)
             * UBSan: signed integer overflow: -862131216 + -2013265920 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000003,time:1221,execs:337,op:havoc,rep:4)
             */
            result = result + x;
        }
        /* Possible weaknesses found:
         * UBSan: left shift of negative value -1837658568 (AFL crash: id:000003,sig:06,src:000003,time:1634,execs:441,op:havoc,rep:5)
         * UBSan: left shift of 1195817184 by 1 places cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000003,time:1083,execs:306,op:havoc,rep:15)
         * UBSan: left shift of 1818787840 by 1 places cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000003,time:1221,execs:337,op:havoc,rep:4)
         * UBSan: left shift of 1766077504 by 1 places cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:7,execs:15,op:(null),pos:0)
         */
        x <<= 1;
        y >>= 1;
    }
    if (negativeResult) {
        result = -result;
    }
    return result;
}

int main() {
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    int product = multiply(a, b);
    printf("Product: %d\n", product);
    return 0;
}