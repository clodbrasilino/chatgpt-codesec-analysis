#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

typedef struct {
    double x;
    double y;
} Tuple;

Tuple exponentiate(Tuple base, Tuple exp) {
    Tuple result;
    /* Possible weaknesses found:
     *  call to undeclared library function 'pow' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
     *  include the header <math.h> or explicitly provide a declaration for 'pow'
     */
    result.x = pow(base.x, exp.x);
    result.y = pow(base.y, exp.y);
    return result;
}

int main() {
    Tuple base = {2.0, 3.0};
    Tuple exp = {3.0, 2.0};
    Tuple result = exponentiate(base, exp);

    printf("Result: (%f, %f)\n", result.x, result.y);
    return 0;
}