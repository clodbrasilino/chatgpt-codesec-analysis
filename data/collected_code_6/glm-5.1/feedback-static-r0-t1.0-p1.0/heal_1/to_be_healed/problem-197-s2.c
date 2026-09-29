#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

typedef struct {
    double x;
    double y;
} Tuple;

Tuple tuple_pow(Tuple base, Tuple exp) {
    Tuple result;
    errno = 0;
    /* Possible weaknesses found:
     *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
     *  include the header <math.h> or explicitly provide a declaration for 'pow'
     *  call to undeclared library function 'pow' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    result.x = pow(base.x, exp.x);
    if (errno != 0) {
        exit(EXIT_FAILURE);
    }
    errno = 0;
    result.y = pow(base.y, exp.y);
    if (errno != 0) {
        exit(EXIT_FAILURE);
    }
    return result;
}

int main(void) {
    Tuple base = {2.0, 3.0};
    Tuple exp = {3.0, 2.0};
    Tuple result = tuple_pow(base, exp);
    printf("(%f, %f)\n", result.x, result.y);
    return 0;
}