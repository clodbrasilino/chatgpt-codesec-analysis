#include <stdio.h>
#include <math.h>

int is_perfect_square(long long num) {
    if (num < 0) {
        return 0;
    }
    if (num == 0) {
        return 1;
    }
    long long root = (long long)sqrt((double)num);
    while (root * root > num) {
        root--;
    }
    while (root < num / root) {
        root++;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 3037000500 * 3037000500 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:325,execs:175,op:havoc,rep:2)
     */
    return root * root == num;
}

int main(void) {
    long long val;
    if (scanf("%lld", &val) == 1) {
        if (is_perfect_square(val)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }
    return 0;
}