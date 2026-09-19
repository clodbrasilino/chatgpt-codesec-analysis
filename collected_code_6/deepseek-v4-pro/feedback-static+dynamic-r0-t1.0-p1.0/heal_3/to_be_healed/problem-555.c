#include <stdio.h>
#include <limits.h>

long long difference(long long n) {
    long long sum_n;
    long long sum_cubes;
    
    if (n < 1) {
        return -1;
    }
    
    if (n % 2 == 0) {
        if (n > LLONG_MAX / (n + 1) * 2) {
            return -1;
        }
        sum_n = n / 2;
        if (sum_n > LLONG_MAX / (n + 1)) {
            return -1;
        }
        sum_n = sum_n * (n + 1);
    } else {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 * 2 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:316,execs:169,op:havoc,rep:1)
         * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:434,execs:221,op:havoc,rep:1)
         */
        if (n + 1 > LLONG_MAX / n * 2) {
            return -1;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:434,execs:221,op:havoc,rep:1)
         */
        sum_n = (n + 1) / 2;
        if (sum_n > LLONG_MAX / n) {
            return -1;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: -4611686018427387904 * 9223372036854775807 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:434,execs:221,op:havoc,rep:1)
         */
        sum_n = sum_n * n;
    }
    
    if (sum_n > 3037000499LL) {
        return -1;
    }
    
    if (sum_n > LLONG_MAX / sum_n) {
        return -1;
    }
    sum_cubes = sum_n * sum_n;
    
    /* Possible weaknesses found:
     *  Assuming that condition 'sum_cubes<sum_n' is not redundant
     */
    if (sum_cubes < sum_n) {
        return -1;
    }
    
    /* Possible weaknesses found:
     *  Condition 'sum_cubes>=sum_n' is always true [knownConditionTrueFalse]
     *  Condition 'sum_cubes>=sum_n' is always true
     *  Condition 'sum_cubes-sum_n<0' is always false
     *  Condition 'sum_cubes-sum_n<0' is always false [knownConditionTrueFalse]
     */
    if (sum_cubes - sum_n < 0 && sum_cubes >= sum_n) {
        return -1;
    }
    
    return sum_cubes - sum_n;
}

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