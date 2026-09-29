#include <stdio.h>
#include <limits.h>

unsigned long long find_max_k(unsigned long long x, unsigned long long y) {
    if (x == 0) {
        return 0;
    }
    if (y >= x) {
        return 0;
    }
    if (x == 1) {
        return 0;
    }
    if (y == ULLONG_MAX % x) {
        return ULLONG_MAX;
    }
    return (ULLONG_MAX / x) * x + y;
}

int main() {
    unsigned long long x = 7;
    unsigned long long y = 3;
    unsigned long long k = find_max_k(x, y);
    printf("%llu\n", k);
    return 0;
}