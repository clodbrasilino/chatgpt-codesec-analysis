#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  'LONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

bool safe_multiply(long a, long b, long* result) {
    /* Possible weaknesses found:
     *  'LONG_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'LONG_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (a > 0 && b > 0 && a > (LONG_MAX / b)) return false;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'LONG_MIN'
     *  'LONG_MIN' undeclared (first use in this function)
     *  'LONG_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     */
    if (a < 0 && b < 0 && a < (LONG_MIN / b)) return false;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'LONG_MIN'
     */
    if (a > 0 && b < 0 && b < (LONG_MIN / a)) return false;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'LONG_MIN'
     */
    if (a < 0 && b > 0 && a < (LONG_MIN / b)) return false;
    *result = a * b;
    return true;
}

bool safe_add(long a, long b, long* result) {
    /* Possible weaknesses found:
     *  'LONG_MAX' undeclared (first use in this function)
     *  'LONG_MIN' undeclared (first use in this function)
     *  'LONG_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  'LONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  use of undeclared identifier 'LONG_MAX'
     *  use of undeclared identifier 'LONG_MIN'
     */
    if ((b > 0 && a > (LONG_MAX - b)) || (b < 0 && a < (LONG_MIN - b))) return false;
    *result = a + b;
    return true;
}

long find_nth_term(long a, long d, long n) {
    if (n <= 0) return 0;

    long temp1, temp2;
    if (!safe_multiply(n - 1, d, &temp1) || !safe_add(a, temp1, &temp2)) {
        return 0; // or handle error as needed
    }
    return temp2;
}

int main() {
    long a, d, n;
    scanf("%ld %ld %ld", &a, &d, &n);
    printf("%ld\n", find_nth_term(a, d, n));
    return 0;
}