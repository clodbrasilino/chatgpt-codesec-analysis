#include <stdio.h>
#include <stdbool.h>

static bool safe_mul(long long a, long long b, long long *res) {
    if (a > 0) {
        if (b > 0) {
            if (a > LLONG_MAX / b) return false;
        } else {
            if (b < LLONG_MIN / a) return false;
        }
    } else {
        if (b > 0) {
            if (a < LLONG_MIN / b) return false;
        } else {
            if (a != 0 && b < LLONG_MAX / a) return false;
        }
    }
    *res = a * b;
    return true;
}

long long find_max_cuboid_volume(long long s) {
    if (s <= 0) {
        return -1;
    }
    if (s % 3 == 0) {
        long long side = s / 3;
        long long res;
        if (!safe_mul(side, side, &res) || !safe_mul(res, side, &res)) {
            return -1;
        }
        return res;
    }
    if (s % 3 == 1) {
        long long side1 = (s - 4) / 3;
        long long side2 = side1 + 1;
        if (side1 < 1) {
            return -1;
        }
        long long res;
        if (!safe_mul(side1, side1, &res) || !safe_mul(res, side2, &res)) {
            return -1;
        }
        return res;
    }
    if (s % 3 == 2) {
        long long side = (s - 2) / 3;
        if (side < 1) {
            return -1;
        }
        long long side2 = side + 1;
        long long res;
        if (!safe_mul(side, side, &res) || !safe_mul(res, side2, &res)) {
            return -1;
        }
        return res;
    }
    return -1;
}

int main(void) {
    long long s;
    if (scanf("%lld", &s) != 1) {
        return 1;
    }
    long long volume = find_max_cuboid_volume(s);
    printf("%lld\n", volume);
    return 0;
}