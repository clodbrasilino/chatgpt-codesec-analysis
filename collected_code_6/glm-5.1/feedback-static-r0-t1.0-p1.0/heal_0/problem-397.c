#include <stdio.h>

int find_median(int a, int b, int c) {
    if ((a >= b && a <= c) || (a >= c && a <= b)) {
        return a;
    }
    if ((b >= a && b <= c) || (b >= c && b <= a)) {
        return b;
    }
    return c;
}

int main(void) {
    int result = find_median(5, 10, 3);
    printf("%d\n", result);
    return 0;
}