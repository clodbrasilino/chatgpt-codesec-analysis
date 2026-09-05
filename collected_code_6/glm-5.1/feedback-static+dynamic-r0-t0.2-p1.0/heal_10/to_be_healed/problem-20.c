#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  */

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }
    if (n == 1) {
        return true;
    }
    for (unsigned long long k = 1; k <= ULLONG_MAX / 2; k++) {
        unsigned long long power = 2 * k;
        if (k > ULLONG_MAX / power) {
            return false;
        }
        power *= k;
        if (power > (ULLONG_MAX - 1) / 2) {
            return false;
        }
        unsigned long long val = power * 2 + 1;
        if (val == n) {
            return true;
        }
        if (val > n) {
            return false;
        }
    }
    return false;
}

int main(void) {
    unsigned long long num = 1;
    if (scanf("%llu", &num) == 1) {
        if (is_woodall(num)) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }
    return 0;
}