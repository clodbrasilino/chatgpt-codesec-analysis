#include <stdio.h>
#include <limits.h>
#include <stdint.h>

long long sum_even_natural_range(long long l, long long r) {
    if (l < 1) {
        l = 1;
    }
    if (r < 1) {
        r = 1;
    }
    if (l > r) {
        return 0;
    }
    if (l % 2 != 0) {
        if (l == LLONG_MAX) {
            return 0;
        }
        l++;
    }
    if (r % 2 != 0) {
        r--;
    }
    if (l > r) {
        return 0;
    }

    unsigned long long ull_l = (unsigned long long)l;
    unsigned long long ull_r = (unsigned long long)r;
    unsigned long long ull_n = (ull_r - ull_l) / 2 + 1;
    unsigned long long ull_sum = ull_l + ull_r;

    if (ull_n % 2 == 0) {
        unsigned long long half_n = ull_n / 2;
        if (half_n > ULLONG_MAX / ull_sum) {
            if (ull_sum == 0) return 0;
            return (long long)((ull_sum / 2) * ull_n);
        }
        return (long long)(half_n * ull_sum);
    } else {
        if (ull_sum % 2 == 0) {
            unsigned long long half_sum = ull_sum / 2;
            if (half_sum > ULLONG_MAX / ull_n) {
                return (long long)((ull_n / 2) * ull_sum);
            }
            return (long long)(half_sum * ull_n);
        } else {
            if (ull_n > ULLONG_MAX / ull_sum) {
                return (long long)((ull_sum / 2) * ull_n + (ull_n / 2));
            }
            return (long long)(ull_n * ull_sum / 2);
        }
    }
}

int main(void) {
    long long l, r;
    if (scanf("%lld %lld", &l, &r) != 2) {
        return 1;
    }
    printf("%lld\n", sum_even_natural_range(l, r));
    return 0;
}