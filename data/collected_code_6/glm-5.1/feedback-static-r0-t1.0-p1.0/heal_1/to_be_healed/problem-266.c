#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  'strerror' is defined in header '<string.h>'; this is probably fixable by adding '#include <string.h>'
  */

double calculate_lateral_surface_area(double side) {
    if (side < 0.0) {
        errno = EDOM;
        return -1.0;
    }
    if (side > (double)(ULLONG_MAX / 4.0)) {
        errno = ERANGE;
        return -1.0;
    }
    return 4.0 * side * side;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <side_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    errno = 0;
    double side = strtod(argv[1], &endptr);

    if (errno == ERANGE || endptr == argv[1] || *endptr != '\0') {
        fprintf(stderr, "Invalid input: Not a valid number\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    double area = calculate_lateral_surface_area(side);

    if (errno != 0) {
        /* Possible weaknesses found:
         *  implicit declaration of function 'strerror' [-Wimplicit-function-declaration]
         *  call to undeclared library function 'strerror' with type 'char *(int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strerror'
         */
        fprintf(stderr, "Error calculating area: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("%.6f\n", area);

    return EXIT_SUCCESS;
}