#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  *  include '<math.h>' or provide a declaration of 'log10l'
  */

int first_factorial_digit(int n) {
    if (n < 0) {
        exit(EXIT_FAILURE);
    }
    if (n == 0) {
        return 1;
    }
    long double log_sum = 0.0L;
    for (int i = 1; i <= n; i++) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'log10l' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'log10l' with type 'long double (long double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <math.h> or explicitly provide a declaration for 'log10l'
         */
        log_sum += log10l(i);
    }
    /* Possible weaknesses found:
     *  implicit declaration of function 'floorl' [-Wimplicit-function-declaration]
     *  include the header <math.h> or explicitly provide a declaration for 'floorl'
     *  include '<math.h>' or provide a declaration of 'floorl'
     *  call to undeclared library function 'floorl' with type 'long double (long double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    long double fractional = log_sum - floorl(log_sum);
    /* Possible weaknesses found:
     *  include the header <math.h> or explicitly provide a declaration for 'powl'
     *  implicit declaration of function 'powl' [-Wimplicit-function-declaration]
     *  include '<math.h>' or provide a declaration of 'powl'
     *  call to undeclared library function 'powl' with type 'long double (long double, long double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    long double first = powl(10.0L, fractional);
    return (int)first;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    long val = strtol(argv[1], NULL, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    int result = first_factorial_digit((int)val);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}