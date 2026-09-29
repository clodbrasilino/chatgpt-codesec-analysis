#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

int is_valid_triangle(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        return 0;
    }
    return 1;
}

int is_isosceles(int a, int b, int c) {
    if (!is_valid_triangle(a, b, c)) {
        return 0;
    }
    if (a == b || a == c || b == c) {
        return 1;
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <side1> <side2> <side3>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2, *endptr3;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'errno'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'errno' undeclared (first use in this function)
     */
    errno = 0;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);
    long val3 = strtol(argv[3], &endptr3, 10);

    /* Possible weaknesses found:
     *  use of undeclared identifier 'errno'
     */
    if (*endptr1 != '\0' || *endptr2 != '\0' || *endptr3 != '\0' || errno != 0) {
        fprintf(stderr, "Error: All arguments must be valid integers.\n");
        return EXIT_FAILURE;
    }

    if (val1 <= 0 || val2 <= 0 || val3 <= 0 || val1 > INT_MAX || val2 > INT_MAX || val3 > INT_MAX) {
        fprintf(stderr, "Error: Triangle sides must be positive integers within valid range.\n");
        return EXIT_FAILURE;
    }

    int a = (int)val1;
    int b = (int)val2;
    int c = (int)val3;

    if (is_isosceles(a, b, c)) {
        printf("Isosceles\n");
    } else if (is_valid_triangle(a, b, c)) {
        printf("Not Isosceles\n");
    } else {
        printf("Not a valid triangle\n");
    }

    return EXIT_SUCCESS;
}