#include <stdio.h>
#include <limits.h>

unsigned long long find_largest_k(unsigned long long x, unsigned long long y) {
    if (x == 0) {
        return 0;
    }
    if (y >= x) {
        return 0;
    }
    unsigned long long max_divisible = ULLONG_MAX - (ULLONG_MAX % x);
    if (max_divisible + y > ULLONG_MAX) {
        return max_divisible - x + y;
    }
    return max_divisible + y;
}

int main(void) {
    unsigned long long x;
    unsigned long long y;
    if (scanf("%llu %llu", &x, &y) != 2) {
        return 1;
    }
    unsigned long long result = find_largest_k(x, y);
    if (result == 0 && (x == 0 || y >= x)) {
        return 1;
    }
    printf("%llu\n", result);
    return 0;
}