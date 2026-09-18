#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_perfect_square(long long num) {
    if (num < 0) {
        return false;
    }
    long long root = (long long)round(sqrt((double)num));
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3037000500 * 3037000500 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:272,execs:150,op:havoc,rep:3)
     */
    return (root * root == num);
}

int main(void) {
    long long num = 0;
    
    if (scanf("%lld", &num) != 1) {
        return 1;
    }
    
    if (is_perfect_square(num)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    
    return 0;
}