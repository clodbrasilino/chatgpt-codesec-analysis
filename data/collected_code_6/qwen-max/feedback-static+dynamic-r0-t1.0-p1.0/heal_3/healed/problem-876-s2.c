#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int64_t gcd(int64_t a, int64_t b) {
    while (b != 0) {
        int64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int64_t lcm(int64_t a, int64_t b) {
    if (a == 0 || b == 0) return 0;
    if (a == INT64_MAX || b == INT64_MAX) return INT64_MAX;
    int64_t gcd_value = gcd(a, b);
    if (INT64_MAX / a < (b / gcd_value)) return INT64_MAX;
    return (a / gcd_value) * b;
}

int main() {
    int64_t x, y;
    printf("Enter two positive integers: ");
    if (scanf("%lld %lld", &x, &y) == 2) {
        if (x > 0 && y > 0) {
            printf("LCM of %lld and %lld is %lld\n", x, y, lcm(x, y));
        } else {
            printf("Please enter positive integers.\n");
        }
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}