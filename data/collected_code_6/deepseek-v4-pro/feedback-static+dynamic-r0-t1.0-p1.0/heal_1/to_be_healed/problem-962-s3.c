#include <stdio.h>

int sum_even_in_range(int l, int r) {
    if (l > r) {
        return 0;
    }
    if (l <= 0) {
        l = 1;
    }
    if (l % 2 != 0) {
        l++;
    }
    if (r % 2 != 0) {
        r--;
    }
    if (l > r) {
        return 0;
    }
    int n = (r - l) / 2 + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 288888 * 577778 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:648,execs:433,op:havoc,rep:1)
     * UBSan: signed integer overflow: 16666665 * 33333336 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000005,time:7256,execs:4650,op:havoc,rep:11)
     */
    return n * (l + r) / 2;
}

int main(void) {
    int l, r;
    printf("Enter lower bound: ");
    if (scanf("%d", &l) != 1) {
        return 1;
    }
    printf("Enter upper bound: ");
    if (scanf("%d", &r) != 1) {
        return 1;
    }
    int result = sum_even_in_range(l, r);
    printf("Sum of even numbers in range [%d, %d]: %d\n", l, r, result);
    return 0;
}