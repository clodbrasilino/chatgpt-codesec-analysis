#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

int is_equilateral(double a, double b, double c) {
    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return 0;
    }
    if (a == b && b == c) {
        return 1;
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    double a, b, c;
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <side_a> <side_b> <side_c>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr_a, *endptr_b, *endptr_c;
    a = strtod(argv[1], &endptr_a);
    b = strtod(argv[2], &endptr_b);
    c = strtod(argv[3], &endptr_c);

    /* Possible weaknesses found:
     *  'errno' undeclared (first use in this function)
     *  use of undeclared identifier 'ERANGE'
     *  use of undeclared identifier 'errno'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'ERANGE' undeclared (first use in this function)
     */
    if (errno == ERANGE || *endptr_a != '\0' || *endptr_b != '\0' || *endptr_c != '\0' || a <= 0.0 || b <= 0.0 || c <= 0.0) {
        fprintf(stderr, "Invalid input: Must be positive numbers\n");
        return EXIT_FAILURE;
    }

    if (is_equilateral(a, b, c)) {
        printf("The triangle is equilateral.\n");
    } else {
        printf("The triangle is not equilateral.\n");
    }

    return EXIT_SUCCESS;
}