#include <stdio.h>

int sum_even_natural_range(int l, int r) {
    if (l < 1) {
        l = 1;
    }
    if (r < 1) {
        r = 1;
    }
    if (l > r) {
        return 0;
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
     * UBSan: signed integer overflow: 50000000 * 766666666 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:822,execs:588,op:havoc,rep:3)
     * UBSan: signed integer overflow: 767908978 * 1535817958 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000001,time:3921,execs:2744,op:havoc,rep:4)
     */
    return n * (l + r) / 2;
}

int main(void) {
    int l, r;
    if (scanf("%d %d", &l, &r) != 2) {
        return 1;
    }
    printf("%d\n", sum_even_natural_range(l, r));
    return 0;
}