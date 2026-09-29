#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }
    unsigned long long power = 2;
    while (1) {
        unsigned long long p = power - 1;
        if (p != 0 && n % p == 0) {
            unsigned long long k = n / p;
            if (k > 0 && (k & (k - 1)) == 0) {
                return true;
            }
        }
        if (p >= n) {
            break;
        }
        if (power > ULLONG_MAX / 2) {
            break;
        }
        power <<= 1;
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