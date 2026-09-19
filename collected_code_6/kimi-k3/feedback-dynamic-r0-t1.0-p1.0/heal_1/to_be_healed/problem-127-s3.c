#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <errno.h>

int safe_multiply(int a, int b, int *result) {
    if (result == NULL) {
        return -1;
    }
    
    if (a == 0 || b == 0) {
        *result = 0;
        return 0;
    }
    
    if (a > 0) {
        if (b > 0) {
            if (a > INT_MAX / b) {
                return -1;
            }
        } else {
            if (b < INT_MIN / a) {
                return -1;
            }
        }
    } else {
        if (b > 0) {
            if (a < INT_MIN / b) {
                return -1;
            }
        } else {
            if (a < INT_MAX / b) {
                return -1;
            }
        }
    }
    
    int abs_a = (a < 0) ? -a : a;
    int abs_b = (b < 0) ? -b : b;
    int product = 0;
    
    while (abs_b > 0) {
        if (abs_b & 1) {
            product += abs_a;
        }
        /* Possible weaknesses found:
         * UBSan: left shift of 1476395008 by 1 places cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000003,time:2613,execs:1644,op:havoc,rep:2)
         * UBSan: left shift of 1073741824 by 1 places cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000005,time:26417,execs:14776,op:havoc,rep:2)
         * UBSan: left shift of 1228654364 by 1 places cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000005,time:23321,execs:13128,op:havoc,rep:2)
         */
        abs_a <<= 1;
        abs_b >>= 1;
    }
    
    if ((a < 0) != (b < 0)) {
        product = -product;
    }
    
    *result = product;
    return 0;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000003,sig:06,src:000018,time:26644,execs:14895,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    int x, y, result;
    
    printf("Enter two integers: ");
    if (scanf("%d %d", &x, &y) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (safe_multiply(x, y, &result) != 0) {
        fprintf(stderr, "Multiplication overflow\n");
        return 1;
    }
    
    printf("Result: %d\n", result);
    return 0;
}