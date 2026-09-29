#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int area_rectangle(int width, int height) {
    if (width < 0 || height < 0) {
        return -1;
    }
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if ((long)width * height > INT_MAX) {
        return -1;
    }
    return width * height;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <width> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long width = strtol(argv[1], &endptr, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     */
    if (*endptr != '\0' || width > INT_MAX) {
        fprintf(stderr, "Invalid input: width must be a valid integer\n");
        return EXIT_FAILURE;
    }

    long height = strtol(argv[2], &endptr, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     */
    if (*endptr != '\0' || height > INT_MAX) {
        fprintf(stderr, "Invalid input: height must be a valid integer\n");
        return EXIT_FAILURE;
    }

    if (width < 0 || height < 0) {
        fprintf(stderr, "Invalid input: dimensions must be non-negative\n");
        return EXIT_FAILURE;
    }

    int result = area_rectangle((int)width, (int)height);
    if (result < 0) {
        fprintf(stderr, "Error calculating area\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}