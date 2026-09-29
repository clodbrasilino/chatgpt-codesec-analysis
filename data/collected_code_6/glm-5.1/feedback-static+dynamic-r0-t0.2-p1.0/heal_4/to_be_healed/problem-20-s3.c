#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  'UINT64_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }
    unsigned long long k = 1;
    while (1) {
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'UINT64_MAX'
         *  'UINT64_MAX' undeclared (first use in this function)
         */
        if (k > UINT64_MAX / k) {
            break;
        }
        /* Possible weaknesses found:
         *  use of undeclared identifier 'UINT64_MAX'
         */
        if (k > (UINT64_MAX - k * k)) {
            break;
        }
        unsigned long long woodall = k * k + k;
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