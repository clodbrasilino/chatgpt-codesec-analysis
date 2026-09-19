#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

long long jacobsthal_lucas(long n) {
    if (n == 0) return 2;
    if (n == 1) return 1;

    int64_t a = 2, b = 1;
    for (long i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'LLONG_MAX'
         *  each undeclared identifier is reported only once for each function it appears in
         *  'LLONG_MAX' undeclared (first use in this function)
         */
        if (b > LLONG_MAX / 2 || (LLONG_MAX - b) / 2 < a) {
            fprintf(stderr, "Overflow detected\n");
            exit(EXIT_FAILURE);
        }
        int64_t c = 2 * a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || n > 61) {
        fprintf(stderr, "n must be between 0 and 61\n");
        return EXIT_FAILURE;
    }

    int64_t result = jacobsthal_lucas(n);
    printf("The %ldth Jacobsthal-Lucas number is: %" PRId64 "\n", n, result);
    return EXIT_SUCCESS;
}