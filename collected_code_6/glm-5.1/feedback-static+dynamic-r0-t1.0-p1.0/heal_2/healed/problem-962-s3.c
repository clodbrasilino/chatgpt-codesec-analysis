#include <stdio.h>
#include <stdbool.h>

static bool safe_add(long long a, long long b, long long *res) {
    if (a > 0 && b > 0 && a > 9223372036854775807LL - b) return false;
    if (a < 0 && b < 0 && a < -9223372036854775807LL - b) return false;
    *res = a + b;
    return true;
}

static bool safe_sub(long long a, long long b, long long *res) {
    if (a >= 0 && b < 0 && a > 9223372036854775807LL + b) return false;
    if (a < 0 && b > 0 && a < -9223372036854775807LL + b) return false;
    *res = a - b;
    return true;
}

static bool safe_mul(long long a, long long b, long long *res) {
    if (a > 0) {
        if (b > 0) {
            if (a > 9223372036854775807LL / b) return false;
        } else if (b < 0) {
            if (b < -9223372036854775807LL / a) return false;
        }
    } else if (a < 0) {
        if (b > 0) {
            if (a < -9223372036854775807LL / b) return false;
        } else if (b < 0) {
            if (a != -1 && b != -1 && -a > 9223372036854775807LL / -b) return false;
        }
    }
    *res = a * b;
    return true;
}

long long sum_even_natural_numbers(long long l, long long r) {
    if (l > r) {
        return 0;
    }
    if (l <= 0) {
        l = 2;
    }
    if (r <= 0) {
        return 0;
    }
    if (l % 2 != 0) {
        if (!safe_add(l, 1, &l)) return -1;
    }
    if (l > r) {
        return 0;
    }
    if (r % 2 != 0) {
        if (!safe_sub(r, 1, &r)) return -1;
    }
    if (l > r) {
        return 0;
    }
    long long diff;
    if (!safe_sub(r, l, &diff)) return -1;
    long long n = (diff / 2) + 1;
    long long temp;
    if (!safe_mul(n, l, &temp)) return -1;
    long long n_minus_1;
    if (!safe_sub(n, 1, &n_minus_1)) return -1;
    long long result;
    if (!safe_add(temp, n_minus_1, &result)) return -1;
    return result;
}

int main() {
    long long l, r;
    if (scanf("%lld %lld", &l, &r) != 2) {
        return 1;
    }
    long long result = sum_even_natural_numbers(l, r);
    printf("%lld\n", result);
    return 0;
}