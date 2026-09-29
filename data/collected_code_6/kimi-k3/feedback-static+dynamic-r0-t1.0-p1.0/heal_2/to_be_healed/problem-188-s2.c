#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>

int canBeProductOfTwoSquares(long long n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    
    long long limit = (long long)sqrt((double)n);
    if (limit < 0) {
        return 0;
    }
    
    /* Possible weaknesses found:
     *  Assignment 'a=0', assigned value is 0
     */
    for (long long a = 0; a <= limit; a++) {
        if (a > 0 && a > LLONG_MAX / a) {
            break;
        }
        /* Possible weaknesses found:
         *  a_sq is assigned 'a*a' here.
         */
        long long a_sq = a * a;
        
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (a_sq > n) {
            break;
        }
        
        /* Possible weaknesses found:
         *  Division by zero. [zerodiv]
         *  Division by zero
         */
        if (n % a_sq == 0) {
            long long b_sq = n / a_sq;
            if (b_sq < 0) {
                continue;
            }
            long long b = (long long)sqrt((double)b_sq);
            
            if (b >= 0 && b <= LLONG_MAX / b && b * b == b_sq) {
                return 1;
            }
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:15,execs:11,op:quick,pos:0; likely memory-safety defect
  */

int main(void) {
    long long num;
    
    if (scanf("%lld", &num) != 1) {
        return 1;
    }
    
    if (canBeProductOfTwoSquares(num)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return 0;
}