#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
 /* Possible weaknesses found:
  *  'LLONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

long long int calculate_pell_number(long n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 2;

    long long int a = 0, b = 1;
    for (long i = 2; i <= n; ++i) {
        /* Possible weaknesses found:
         *  expected ')' before '__int128_t'
         *  expected ')'
         *  to match this '('
         */
        __int128_t c = 2 * (unsigned __int128_t)b + a;
        /* Possible weaknesses found:
         *  use of undeclared identifier 'LLONG_MIN'
         *  'LLONG_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'LLONG_MAX'
         *  'LLONG_MIN' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  'LLONG_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         */
        if (c > LLONG_MAX || c < LLONG_MIN) {
            fprintf(stderr, "Overflow detected.\n");
            exit(EXIT_FAILURE);
        }
        a = b;
        b = (long long int)c;
    }
    return b;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    long long int result = calculate_pell_number(n);
    printf("The %ldth Pell number is: %lld\n", n, result);

    return 0;
}