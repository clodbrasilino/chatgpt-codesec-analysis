#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int calculate_perimeter(int length, int width) {
    int perimeter = 2 * (length + width);
    return perimeter;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <length> <width>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long length = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || length <= 0) {
        return EXIT_FAILURE;
    }

    long width = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || width <= 0) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (length > INT_MAX / 2 || width > INT_MAX / 2 || length + width > INT_MAX / 2) {
        return EXIT_FAILURE;
    }

    int result = calculate_perimeter((int)length, (int)width);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}