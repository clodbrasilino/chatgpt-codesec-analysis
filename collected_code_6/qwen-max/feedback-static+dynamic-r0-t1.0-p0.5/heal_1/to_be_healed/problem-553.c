#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

double tuple_to_float(const int *tuple, size_t length) {
    if (length == 0) return 0.0;
    double result = 0.0;
    for (size_t i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'pow' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <math.h> or explicitly provide a declaration for 'pow'
         */
        result += tuple[i] * pow(10, length - i - 1);
    }
    return result;
}

int main() {
    int tuple[] = {1, 2, 3, 4};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    double float_value = tuple_to_float(tuple, length);
    printf("%.1f\n", float_value);
    return 0;
}