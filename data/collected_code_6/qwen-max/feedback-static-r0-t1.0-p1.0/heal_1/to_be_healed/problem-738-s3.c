#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

double geometric_sum(int n) {
    if (n < 0) {
        return 0.0;
    }
    if (n == 0) {
        return 1.0;
    }
    /* Possible weaknesses found:
     *  call to undeclared library function 'pow' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
     *  include the header <math.h> or explicitly provide a declaration for 'pow'
     */
    return 1 / pow(2, n) + geometric_sum(n - 1);
}

int main() {
    int n;
    printf("Enter an integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }
    double result = geometric_sum(n);
    printf("Geometric sum of %d is: %.10f\n", n, result);
    return EXIT_SUCCESS;
}