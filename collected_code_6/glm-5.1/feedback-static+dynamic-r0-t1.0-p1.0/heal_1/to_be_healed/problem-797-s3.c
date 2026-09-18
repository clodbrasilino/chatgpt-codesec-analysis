#include <stdio.h>

int sum_odd_natural_numbers(int l, int r) {
    if (l <= 0) {
        l = 1;
    }
    if (r < l) {
        return 0;
    }
    if (l % 2 == 0) {
        l++;
    }
    if (r % 2 == 0) {
        r--;
    }
    if (l > r) {
        return 0;
    }
    int n = ((r - l) / 2) + 1;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 30716356 * 61432724 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000005,time:2775,execs:1754,op:havoc,rep:1)
     * UBSan: signed integer overflow: 138223615 * 276447234 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000004,time:5900,execs:3691,op:havoc,rep:10)
     */
    return n * (l + r) / 2;
}

int main() {
    int l, r;
    if (scanf("%d %d", &l, &r) != 2) {
        return 1;
    }
    int result = sum_odd_natural_numbers(l, r);
    printf("%d\n", result);
    return 0;
}