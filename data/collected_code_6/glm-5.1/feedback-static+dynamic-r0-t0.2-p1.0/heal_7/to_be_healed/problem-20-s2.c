#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  'ULLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
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
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'ULLONG_MAX'
         *  'ULLONG_MAX' undeclared (first use in this function)
         */
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