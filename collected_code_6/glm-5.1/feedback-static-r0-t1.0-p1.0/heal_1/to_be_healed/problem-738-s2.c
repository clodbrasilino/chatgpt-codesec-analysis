#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

double geometric_sum(int n, double r) {
    if (n < 1) {
        return 0.0;
    }
    if (r == 1.0) {
        return (double)(n - 1);
    }
    /* Possible weaknesses found:
     *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
     *  include the header <math.h> or explicitly provide a declaration for 'pow'
     *  call to undeclared library function 'pow' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    return (1.0 - pow(r, (double)(n - 1))) / (1.0 - r);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;
    double r;
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    if (sscanf(argv[2], "%lf", &r) != 1) {
        return EXIT_FAILURE;
    }
    if (n < 1) {
        return EXIT_FAILURE;
    }
    double result = geometric_sum(n, r);
    printf("%.6f\n", result);
    return EXIT_SUCCESS;
}