#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

long long count_cubes(long n, long k) {
    /* Possible weaknesses found:
     *  'LLONG_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'LLONG_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (n - k + 1 > LLONG_MAX / (n - k + 1)) {
        return 0;
    }
    long long result = (n - k + 1);
    result *= result;
    return result * (n - k + 1);
}

int main() {
    long n, k;
    if (scanf("%ld %ld", &n, &k) != 2 || n < k || k <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    printf("%lld\n", count_cubes(n, k));
    return EXIT_SUCCESS;
}