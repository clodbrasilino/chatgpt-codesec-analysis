#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'pow'
  */

int tuple_to_int(const int *tuple, size_t length) {
    int result = 0;
    for (size_t i = 0; i < length; ++i) {
        /* Possible weaknesses found:
         *  call to undeclared library function 'pow' with type 'double (double, double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'pow' [-Wimplicit-function-declaration]
         *  include the header <math.h> or explicitly provide a declaration for 'pow'
         */
        result += tuple[i] * pow(10, 3 * (length - i - 1));
    }
    return result;
}

int main() {
    int tuple[] = {1, 2, 3};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    int result = tuple_to_int(tuple, length);
    printf("%d\n", result);
    return 0;
}