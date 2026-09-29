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
             * UBSan: signed integer overflow: 2147483647 - -1025293812 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000000,time:4526,execs:2980,op:havoc,rep:14)
             * UBSan: signed integer overflow: 2147483647 - -1116077172 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:368,execs:291,op:havoc,rep:15)
             * UBSan: signed integer overflow: 2147483647 - -637353989 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000000,time:901,execs:611,op:havoc,rep:15)
             */
            if (result > INT_MAX - x || (result < 0 && x < 0 && result < INT_MIN - x)) {
                return 0;
            }
            result += x;
        }
        if (x > 0 && (x > INT_MAX / 2 || (x < 0 && x < INT_MIN / 2))) {
            return 0;
        }
        /* Possible weaknesses found:
         * UBSan: left shift of negative value -279019293 (AFL crash: id:000000,sig:06,src:000000,time:368,execs:291,op:havoc,rep:15)
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