#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }
    unsigned long long k = 1;
    while (1) {
        if (k > UINT64_MAX / k) {
            break;
        }
        unsigned long long kk = k * k;
        if (UINT64_MAX - kk < k) {
            break;
        }
        unsigned long long woodall = kk + k;
        if (woodall == n) {
            return true;
        }
        if (woodall > n) {
            break;
        }
        k++;
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