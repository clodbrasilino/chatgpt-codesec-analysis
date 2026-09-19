#include <stdio.h>

long long difference(long long n) {
    long long sum_n;
    long long sum_cubes;
    
    if (n % 2 == 0) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 111136111111 * 222272222223 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000004,time:1338,execs:446,op:havoc,rep:2)
         */
        sum_n = n / 2 * (n + 1);
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:406,execs:148,op:havoc,rep:3)
         * UBSan: signed integer overflow: -4611686018427387904 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000003,time:406,execs:148,op:havoc,rep:3)
         */
        sum_n = (n + 1) / 2 * n;
    }
    
    if (sum_n < 0) {
        return -1;
    }
    
    if (sum_n > 3037000499LL) {
        return -1;
    }
    
    sum_cubes = sum_n * sum_n;
    
    if (sum_cubes < sum_n) {
        return -1;
    }
    
    return sum_cubes - sum_n;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:123,execs:57,op:havoc,rep:14; likely memory-safety defect
  */

int main(void) {
    long long n;
    
    printf("Enter a natural number: ");
    if (scanf("%lld", &n) != 1 || n < 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    long long result = difference(n);
    if (result == -1) {
        printf("Overflow occurred\n");
        return 1;
    }
    
    printf("Difference: %lld\n", result);
    
    return 0;
}