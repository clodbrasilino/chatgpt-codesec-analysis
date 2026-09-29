#include <stdio.h>

void find_numbers(long long l, long long r, long long *x, long long *y) {
    if (l * 2 <= r) {
        *x = l;
        *y = l * 2;
    } else {
        *x = -1;
        *y = -1;
    }
}

int main(void) {
    long long l;
    long long r;
    long long x;
    long long y;

    if (scanf("%lld %lld", &l, &r) == 2) {
        if (l > 0 && r > 0 && l <= r) {
            find_numbers(l, r, &x, &y);
            if (x != -1 && y != -1) {
                printf("%lld %lld\n", x, y);
            } else {
                printf("-1 -1\n");
            }
        } else {
            printf("-1 -1\n");
        }
    }

    return 0;
}