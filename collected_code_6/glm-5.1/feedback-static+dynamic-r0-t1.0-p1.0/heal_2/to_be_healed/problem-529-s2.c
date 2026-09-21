#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

unsigned long long jacobsthal_lucas(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }
    unsigned long long a = 2;
    unsigned long long b = 1;
    for (int i = 2; i <= n; i++) {
        unsigned long long c = b + 2 * a;
        a = b;
        b = c;
    }
    return b;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    long n_long = strtol(argv[1], NULL, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (n_long < 0 || n_long > INT_MAX) {
        return EXIT_FAILURE;
    }
    int n = (int)n_long;
    unsigned long long result = jacobsthal_lucas(n);
    printf("%llu\n", result);
    return EXIT_SUCCESS;
}