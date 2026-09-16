#include <stdio.h>
#include <stdlib.h>

long long count_internal_points(long long x1, long long y1, long long x2, long long y2) {
    long long dx = (x2 > x1) ? (x2 - x1) : (x1 - x2);
    long long dy = (y2 > y1) ? (y2 - y1) : (y1 - y2);

    if (dx <= 1 || dy <= 1) {
        return 0;
    }

    return (dx - 1) * (dy - 1);
}

int main(void) {
    long long x1 = 0;
    long long y1 = 0;
    long long x2 = 5;
    long long y2 = 5;

    long long result = count_internal_points(x1, y1, x2, y2);

    if (printf("%lld\n", result) < 0) {
        return 1;
    }

    return 0;
}