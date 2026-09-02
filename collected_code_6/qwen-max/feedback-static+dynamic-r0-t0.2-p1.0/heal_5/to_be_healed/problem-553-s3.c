#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

double tuple_to_float(const int *tuple, size_t len) {
    if (len == 0) return 0.0;
    double result = 0.0;
    for (size_t i = 0; i < len; ++i) {
        /* Possible weaknesses found:
         *  include the header <math.h> or explicitly provide a declaration for 'pow'
         *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'pow' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         */
        result += tuple[i] * (10.0 * (len - 1 - i) == 0 ? 1 : pow(10, len - 1 - i));
    }
    return result / (len - 1);
}

int main() {
    int tuple[] = {7, 2, 5, 6};
    size_t len = sizeof(tuple) / sizeof(tuple[0]);
    double float_value = tuple_to_float(tuple, len);
    printf("%.4f\n", float_value);

    int tuple2[] = {8, 1, 2, 3};
    len = sizeof(tuple2) / sizeof(tuple2[0]);
    float_value = tuple_to_float(tuple2, len);
    printf("%.4f\n", float_value);

    int tuple3[] = {4, 5, 6};
    len = sizeof(tuple3) / sizeof(tuple3[0]);
    float_value = tuple_to_float(tuple3, len);
    printf("%.4f\n", float_value);

    return 0;
}