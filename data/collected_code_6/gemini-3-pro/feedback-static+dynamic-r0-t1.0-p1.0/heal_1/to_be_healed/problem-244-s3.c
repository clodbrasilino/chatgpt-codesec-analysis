#include <stdio.h>
#include <math.h>

long long find_next_perfect_square(long long n) {
    if (n < 0) {
        return 0;
    }
    long long root = (long long)floor(sqrt((double)n));
    long long next_root = root + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3037000500 * 3037000500 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:2624,execs:1283,op:havoc,rep:9)
     */
    return next_root * next_root;
}

int main(void) {
    long long num;
    
    if (scanf("%lld", &num) != 1) {
        return 1;
    }
    
    long long result = find_next_perfect_square(num);
    printf("%lld\n", result);
    
    return 0;
}