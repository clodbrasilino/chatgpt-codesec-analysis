#include <stdio.h>

int find_median(int a, int b, int c) {
    if ((a >= b && a <= c) || (a <= b && a >= c)) {
        return a;
    } else if ((b >= a && b <= c) || (b <= a && b >= c)) {
        return b;
    } else {
        return c;
    }
}

int main(void) {
    int result = find_median(5, 10, 3);
    printf("%d\n", result);
    return 0;
}