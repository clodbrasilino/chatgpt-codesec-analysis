#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  *  include '<math.h>' or provide a declaration of 'sqrt'
  */

int count_odd_factors(int lower, int upper) {
    if (lower > upper) {
        return 0;
    }

    int count = 0;
    for (int i = lower; i <= upper; i++) {
        if (i <= 0) {
            continue;
        }
        /* Possible weaknesses found:
         *  call to undeclared library function 'sqrt' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
         *  include the header <math.h> or explicitly provide a declaration for 'sqrt'
         */
        int root = (int)sqrt(i);
        if (root * root == i) {
            count++;
        }
    }
    return count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lower> <upper>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_lower, *endptr_upper;
    long lower_l = strtol(argv[1], &endptr_lower, 10);
    long upper_l = strtol(argv[2], &endptr_upper, 10);

    if (*endptr_lower != '\0' || *endptr_upper != '\0') {
        fprintf(stderr, "Invalid input: arguments must be integers\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  'INT_MIN' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' undeclared (first use in this function)
     */
    if (lower_l > INT_MAX || upper_l > INT_MAX || lower_l < INT_MIN || upper_l < INT_MIN) {
        fprintf(stderr, "Invalid input: arguments out of int range\n");
        return EXIT_FAILURE;
    }

    int lower = (int)lower_l;
    int upper = (int)upper_l;

    int result = count_odd_factors(lower, upper);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}