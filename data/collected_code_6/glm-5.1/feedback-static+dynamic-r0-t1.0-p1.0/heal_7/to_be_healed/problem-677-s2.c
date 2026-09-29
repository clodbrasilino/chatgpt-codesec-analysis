#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'LONG_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int is_valid_triangle(long a, long b, long c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'LONG_MAX'
     *  'LONG_MAX' undeclared (first use in this function)
     */
    if (a > LONG_MAX - b || a + b <= c) {
        return 0;
    }
    /* Possible weaknesses found:
     *  use of undeclared identifier 'LONG_MAX'
     */
    if (b > LONG_MAX - c || b + c <= a) {
        return 0;
    }
    /* Possible weaknesses found:
     *  use of undeclared identifier 'LONG_MAX'
     */
    if (a > LONG_MAX - c || a + c <= b) {
        return 0;
    }
    return 1;
}

int main(void) {
    long a, b, c;
    if (scanf("%ld %ld %ld", &a, &b, &c) != 3) {
        return EXIT_FAILURE;
    }
    if (is_valid_triangle(a, b, c)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return EXIT_SUCCESS;
}