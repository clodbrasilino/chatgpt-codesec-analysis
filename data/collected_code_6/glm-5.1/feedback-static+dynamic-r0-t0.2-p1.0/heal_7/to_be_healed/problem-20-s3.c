#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  */

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
    if (k <= UINT64_MAX / 2 && k * 2 <= UINT64_MAX / k) {
        unsigned long long p2 = k * 2;
        unsigned long long p2k = p2 * k;
        if (UINT64_MAX - p2k >= 2) {
            unsigned long long woodall_prime = p2k + 2;
            if (woodall_prime == n) {
                return true;
            }
            if (woodall_prime > n) {
                return false;
            }
        }
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