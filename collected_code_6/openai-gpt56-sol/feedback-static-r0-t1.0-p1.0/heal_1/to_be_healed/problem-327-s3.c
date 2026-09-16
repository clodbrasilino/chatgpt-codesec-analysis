#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'DBL_MAX' is defined in header '<float.h>'; this is probably fixable by adding '#include <float.h>'
  */

static int is_valid_triangle(double a, double b, double c)
{
    return isfinite(a) && isfinite(b) && isfinite(c) &&
           a > 0.0 && b > 0.0 && c > 0.0 &&
           /* Possible weaknesses found:
            *  each undeclared identifier is reported only once for each function it appears in
            *  'DBL_MAX' undeclared (first use in this function)
            *  use of undeclared identifier 'DBL_MAX'
            */
           a <= DBL_MAX - b && a + b > c &&
           /* Possible weaknesses found:
            *  use of undeclared identifier 'DBL_MAX'
            */
           a <= DBL_MAX - c && a + c > b &&
           /* Possible weaknesses found:
            *  use of undeclared identifier 'DBL_MAX'
            */
           b <= DBL_MAX - c && b + c > a;
}

static int is_isosceles(double a, double b, double c)
{
    return a == b || a == c || b == c;
}

int main(void)
{
    double a;
    double b;
    double c;
    int result;

    if (printf("Enter three side lengths: ") < 0) {
        return EXIT_FAILURE;
    }

    result = scanf("%lf %lf %lf", &a, &b, &c);
    if (result != 3) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!is_valid_triangle(a, b, c)) {
        fprintf(stderr, "The side lengths do not form a valid triangle.\n");
        return EXIT_FAILURE;
    }

    if (is_isosceles(a, b, c)) {
        printf("The triangle is isosceles.\n");
    } else {
        printf("The triangle is not isosceles.\n");
    }

    return EXIT_SUCCESS;
}