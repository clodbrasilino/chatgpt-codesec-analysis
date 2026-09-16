#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

double tuple_to_float(const int *tuple, size_t len) {
    if (len == 0) return 0.0;
    /* Possible weaknesses found:
     *  Assuming that condition 'len==1' is not redundant
     */
    if (len == 1) return (double)tuple[0] / 10.0;

    double result = 0.0;
    for (size_t i = 0; i < len; ++i) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'pow' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <math.h> or explicitly provide a declaration for 'pow'
         */
        result += (double)tuple[i] * pow(10, (len - i - 2));
    }
    /* Possible weaknesses found:
     *  Condition 'len>1' is always true [knownConditionTrueFalse]
     *  Condition 'len>1' is always true
     */
    if (len > 1) {
        result /= pow(10, len - 1);
    }
    return result;
}

int main() {
    int tuple[] = {3, 1, 4, 1, 5};
    size_t len = sizeof(tuple) / sizeof(tuple[0]);

    double result = tuple_to_float(tuple, len);
    printf("The float value is: %f\n", result);

    return 0;
}