#include <stdio.h>
#include <math.h>
#include <limits.h>

int canBeProductOfTwoSquares(long long n) {
    if (n < 0) {
        return 0;
    }
    if (n == 0) {
        return 1;
    }
    
    long long limit = (long long)sqrt((double)n);
    
    for (long long a = 0; a <= limit; a++) {
        if (a > 0 && a > LLONG_MAX / a) {
            break;
        }
        long long a_sq = a * a;
        
        if (a_sq > n) {
            break;
        }
        
        if (n % a_sq == 0) {
            long long b_sq = n / a_sq;
            long long b = (long long)sqrt((double)b_sq);
            
            if (b * b == b_sq) {
                return 1;
            }
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:189,execs:88,op:havoc,rep:4; likely memory-safety defect
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