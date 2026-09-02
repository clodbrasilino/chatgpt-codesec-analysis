#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

double geometric_nth_term(double a, double r, unsigned int n) {
    /* Possible weaknesses found:
     *  call to undeclared library function 'pow' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
     *  include the header <math.h> or explicitly provide a declaration for 'pow'
     */
    return a * pow(r, n - 1);
}

int main() {
    double a = 1.0;
    double r = 2.0;
    unsigned int n = 10;
    
    double result = geometric_nth_term(a, r, n);
    printf("The %uth term of the geometric series is: %f\n", n, result);
    return 0;
}