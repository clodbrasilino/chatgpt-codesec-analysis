#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'ldexp'
  */

double geometric_sum(int n) {
    if (n <= 0) {
        return 0.0;
    }
    if (n >= 64) {
        return 2.0;
    }
    if (n >= 53) {
        return 2.0;
    }
    /* Possible weaknesses found:
     *  include the header <math.h> or explicitly provide a declaration for 'ldexp'
     *  implicit declaration of function 'ldexp' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'ldexp' with type 'double (double, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    return 2.0 - ldexp(1.0, -(n - 1));
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    double result = geometric_sum((int)val);
    printf("%.8f\n", result);
    fflush(stdout);
    return EXIT_SUCCESS;
}