#include <stdio.h>
#include <limits.h>

int multiply(int x, int y) {
    long long result = 0;
    if (y < 0) {
        y = -y;
        x = -x;
    }
    while (y > 0) {
        if (y & 1) {
            if (result > INT_MAX || result < INT_MIN) {
                return 0;
            }
            result += x;
        }
        if (x > 0 && (x > INT_MAX / 2)) {
            return 0;
        }
        if (x < 0 && (x < INT_MIN / 2)) {
            return 0;
        }
        /* Possible weaknesses found:
         * UBSan: left shift of negative value -1 (AFL crash: id:000001,sig:06,src:000003,time:494,execs:296,op:havoc,rep:2)
         * UBSan: left shift of negative value -4 (AFL crash: id:000000,sig:06,src:000003,time:347,execs:212,op:arith8,pos:1,val:+35)
         */
        x = (long long)x << 1;
        y >>= 1;
    }
    if (result > INT_MAX || result < INT_MIN) {
        return 0;
    }
    return (int)result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000003,time:1410,execs:706,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    int product = multiply(a, b);
    printf("Product: %d\n", product);
    return 0;
}