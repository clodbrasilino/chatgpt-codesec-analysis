#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<ctype.h>' or provide a declaration of 'isspace'
  */

double tuple_to_float(const char *tuple) {
    const char *start = strchr(tuple, '(');
    if (start == NULL) return 0.0;

    start += 1;
    const char *end;
    double result = strtod(start, (char **)&end);

    /* Possible weaknesses found:
     *  call to undeclared library function 'isspace' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <ctype.h> or explicitly provide a declaration for 'isspace'
     *  implicit declaration of function 'isspace' [-Wimplicit-function-declaration]
     */
    while (*end && isspace(*end)) end++;

    if (*end != ')') return 0.0;

    return result;
}

int main() {
    const char *test_tuples[] = {"(4.56)", "(7.256)", "(8.123)"};
    for (size_t i = 0; i < 3; ++i) {
        double result = tuple_to_float(test_tuples[i]);
        printf("Converted float: %f\n", result);
    }
    return 0;
}