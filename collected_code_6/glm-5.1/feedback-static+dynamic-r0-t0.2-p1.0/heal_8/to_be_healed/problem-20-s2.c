#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected False, got 1
  *  test case 0 failed: expected True, got 0
  */

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }
    unsigned long long power = 1;
    while (1) {
        unsigned long long x = (power << 1) - 1;
        if (x != 0 && n % x == 0) {
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