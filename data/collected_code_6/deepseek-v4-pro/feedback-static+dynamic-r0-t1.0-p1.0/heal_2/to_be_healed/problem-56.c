#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

bool reverse_number(int n, int *result) {
    *result = 0;
    int remaining = n;
    while (remaining != 0) {
        int digit = remaining % 10;
        if (*result > INT_MAX / 10 || *result < INT_MIN / 10) {
            return false;
        }
        if (*result > 0 && *result > (INT_MAX - digit) / 10) {
            return false;
        }
        if (*result < 0 && *result < (INT_MIN - digit) / 10) {
            return false;
        }
        *result = *result * 10 + digit;
        remaining /= 10;
    }
    return true;
}

bool is_one_less_than_twice_reverse(int n) {
    int rev;
    if (!reverse_number(n, &rev)) {
        return false;
    }
    if (rev > INT_MAX / 2 || rev < INT_MIN / 2) {
        return false;
    }
    int twice_rev = 2 * rev;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2147483647 + 1 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000000,time:200,execs:132,op:havoc,rep:2)
     */
    if (twice_rev > 0 && twice_rev > INT_MAX + 1) {
        return false;
    }
    if (twice_rev < 0 && twice_rev < INT_MIN + 1) {
        return false;
    }
    return n == twice_rev - 1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000000,time:295,execs:190,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    
    if (is_one_less_than_twice_reverse(num)) {
        printf("%d is one less than twice its reverse.\n", num);
    } else {
        printf("%d is not one less than twice its reverse.\n", num);
    }
    
    return 0;
}