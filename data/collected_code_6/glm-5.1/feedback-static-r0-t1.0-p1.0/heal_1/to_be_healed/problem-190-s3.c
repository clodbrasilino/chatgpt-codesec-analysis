#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

typedef struct {
    int x;
    int y;
} Point;

long long count_integral_points_inside_square(Point p1, Point p2) {
    long long x_min = (long long)p1.x < p2.x ? p1.x : p2.x;
    long long x_max = (long long)p1.x > p2.x ? p1.x : p2.x;
    long long y_min = (long long)p1.y < p2.y ? p1.y : p2.y;
    long long y_max = (long long)p1.y > p2.y ? p1.y : p2.y;

    long long length = x_max - x_min;
    long long width = y_max - y_min;

    if (length < 2 || width < 2 || length != width) {
        return 0;
    }

    long long inner_length = length - 1;

    return inner_length * inner_length;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <x1> <y1> <x2> <y2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val;

    val = strtol(argv[1], &endptr, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MIN' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  'INT_MAX' undeclared (first use in this function)
     */
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) return EXIT_FAILURE;
    int x1 = (int)val;

    val = strtol(argv[2], &endptr, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  use of undeclared identifier 'INT_MIN'
     */
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) return EXIT_FAILURE;
    int y1 = (int)val;

    val = strtol(argv[3], &endptr, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  use of undeclared identifier 'INT_MIN'
     */
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) return EXIT_FAILURE;
    int x2 = (int)val;

    val = strtol(argv[4], &endptr, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  use of undeclared identifier 'INT_MIN'
     */
    if (*endptr != '\0' || val < INT_MIN || val > INT_MAX) return EXIT_FAILURE;
    int y2 = (int)val;

    Point p1 = {x1, y1};
    Point p2 = {x2, y2};

    long long result = count_integral_points_inside_square(p1, p2);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}