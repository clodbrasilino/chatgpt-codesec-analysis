#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

bool isInSequence(long long a, long long d, long long num) {
    if (d == 0) {
        return a == num;
    }
    if ((d > 0 && num < a) || (d < 0 && num > a)) {
        return false;
    }
    long long diff;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'LLONG_MAX'
     *  'LLONG_MIN' undeclared (first use in this function)
     *  'LLONG_MAX' undeclared (first use in this function)
     *  'LLONG_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  use of undeclared identifier 'LLONG_MIN'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if ((num >= 0 && a < 0 && num > LLONG_MAX + a) || (num < 0 && a > 0 && num < LLONG_MIN + a)) {
        return false;
    }
    diff = num - a;
    if (diff == 0) {
        return true;
    }
    if ((diff > 0 && d < 0) || (diff < 0 && d > 0)) {
        return false;
    }
    /* Possible weaknesses found:
     *  use of undeclared identifier 'LLONG_MIN'
     */
    if ((diff == LLONG_MIN && d == -1)) {
        return true;
    }
    return diff % d == 0;
}

int main() {
    long long a, d, num;
    if (scanf("%lld %lld %lld", &a, &d, &num) != 3) {
        return 1;
    }
    if (isInSequence(a, d, num)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return 0;
}