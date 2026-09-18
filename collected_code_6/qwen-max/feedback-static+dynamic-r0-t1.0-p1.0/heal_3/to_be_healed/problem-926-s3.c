#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  'LONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

bool is_overflow(long a, long b) {
    /* Possible weaknesses found:
     *  'LONG_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'LONG_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (b > 0 && a > LONG_MAX - b) return true;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'LONG_MIN'
     *  'LONG_MIN' undeclared (first use in this function)
     *  'LONG_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     */
    if (b < 0 && a < LONG_MIN - b) return true;
    return false;
}

long derangement(long n) {
    long a = 1, b = 0;
    for (long i = 0; i <= n; ++i) {
        long temp = (i + 1) * (a + b);
        if (is_overflow(b, temp)) return -1;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) return 1;
    if (n < 0) return 1;
    long result = derangement(n);
    if (result == -1) {
        printf("Computation overflowed.\n");
    } else {
        printf("The %ld-th derangement number is: %ld\n", n, result);
    }
    return 0;
}