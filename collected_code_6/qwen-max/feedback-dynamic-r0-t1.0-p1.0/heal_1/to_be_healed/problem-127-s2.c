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
             * UBSan: signed integer overflow: 1677230016 + 1941962752 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:20,execs:15,op:(null),pos:0)
             * UBSan: signed integer overflow: 280087408 + 1886388224 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:1135,execs:574,op:havoc,rep:2)
             */
            result = result + x;
        }
        /* Possible weaknesses found:
         * UBSan: left shift of 1342177280 by 1 places cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000002,time:4047,execs:1750,op:havoc,rep:2)
         * UBSan: left shift of 1199545584 by 1 places cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:20,execs:15,op:(null),pos:0)
         * UBSan: left shift of 2109849600 by 1 places cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000002,time:1135,execs:574,op:havoc,rep:2)
         * UBSan: left shift of negative value -1 (AFL crash: id:000003,sig:06,src:000002,time:8546,execs:3475,op:havoc,rep:2)
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