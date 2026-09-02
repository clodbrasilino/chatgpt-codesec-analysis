#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

double tuple_to_float(const int *tuple, size_t len) {
    double result = 0.0;
    for (size_t i = 0; i < len; ++i) {
        /* Possible weaknesses found:
         *  include the header <math.h> or explicitly provide a declaration for 'pow'
         *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'pow' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        result += tuple[len - 1 - i] * pow(10, i);
    }
    return result / (pow(10, len - 1));
}

int main() {
    int tuple[] = {7, 2, 5, 6};
    size_t len = sizeof(tuple) / sizeof(tuple[0]);
    double float_value = tuple_to_float(tuple, len);
    printf("%.3f\n", float_value);

    int tuple2[] = {8, 1, 2, 3};
    len = sizeof(tuple2) / sizeof(tuple2[0]);
    float_value = tuple_to_float(tuple2, len);
    printf("%.3f\n", float_value);

    int tuple3[] = {4, 5, 6};
    len = sizeof(tuple3) / sizeof(tuple3[0]);
    float_value = tuple_to_float(tuple3, len);
    printf("%.3f\n", float_value);

    return 0;
}