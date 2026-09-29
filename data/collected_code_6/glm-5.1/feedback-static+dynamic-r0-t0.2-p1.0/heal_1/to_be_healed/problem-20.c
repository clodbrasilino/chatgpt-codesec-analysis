#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  'ULLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

bool is_woodall(unsigned long long n) {
    if (n == 0) {
        return false;
    }
    unsigned long long i = 1;
    unsigned long long val = 1;
    while (val < n) {
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'ULLONG_MAX'
         *  'ULLONG_MAX' undeclared (first use in this function)
         */
        if (i > ULLONG_MAX / 2) {
            return false;
        }
        i++;
        /* Possible weaknesses found:
         *  use of undeclared identifier 'ULLONG_MAX'
         */
        if (i > ULLONG_MAX / i) {
            return false;
        }
        val = i * i;
        /* Possible weaknesses found:
         *  use of undeclared identifier 'ULLONG_MAX'
         */
        if (val > ULLONG_MAX - i) {
            return false;
        }
        val += i;
        val--;
    }
    return val == n;
}

int main(void) {
    unsigned long long num;
    if (scanf("%llu", &num) == 1) {
        if (is_woodall(num)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}