#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }
    unsigned long long power = 1;
    while (1) {
        unsigned long long x = power * 2 - 1;
        if (n % x == 0) {
            unsigned long long k = n / x;
            if (k > 0 && (k & (k - 1)) == 0) {
                return true;
            }
        }
        if (x >= n) {
            break;
        }
        if (power > ULLONG_MAX / 2) {
            break;
        }
        power *= 2;
    }
    return false;
}

int main(void) {
    unsigned long long num;
    if (scanf("%llu", &num) == 1) {
        if (is_woodall(num)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}