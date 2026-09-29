#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int max_segments(int n, int a, int b, int c) {
    if (n == 0) return 0;
    if (n < 0) return INT_MIN;

    int res1 = INT_MIN, res2 = INT_MIN, res3 = INT_MIN;

    if (a > 0 && n >= a) res1 = max_segments(n - a, a, b, c);
    if (b > 0 && n >= b) res2 = max_segments(n - b, a, b, c);
    if (c > 0 && n >= c) res3 = max_segments(n - c, a, b, c);

    int max = res1;
    if (res2 > max) max = res2;
    if (res3 > max) max = res3;

    if (max == INT_MIN) return INT_MIN;
    return max + 1;
}

int main(void) {
    int n, a, b, c;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) return 1;

    printf("Enter a, b, c: ");
    if (scanf("%d %d %d", &a, &b, &c) != 3) return 1;

    if (n < 0) {
        printf("Maximum segments: -1\n");
        return 0;
    }

    if (a <= 0 && b <= 0 && c <= 0) {
        printf("Maximum segments: -1\n");
        return 0;
    }

    int result = max_segments(n, a, b, c);
    if (result == INT_MIN) result = -1;

    printf("Maximum segments: %d\n", result);
    return 0;
}