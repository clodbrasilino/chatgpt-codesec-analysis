#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

double geometric_sum(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    /* Possible weaknesses found:
     *  call to undeclared library function 'pow' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
     *  include the header <math.h> or explicitly provide a declaration for 'pow'
     */
    return 1 / pow(2, n) + geometric_sum(n - 1);
}

int main() {
    int n = 5;
    printf("Geometric sum: %f\n", geometric_sum(n));
    return 0;
}