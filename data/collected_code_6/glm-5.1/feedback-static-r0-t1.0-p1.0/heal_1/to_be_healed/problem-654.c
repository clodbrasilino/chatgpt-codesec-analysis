#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int calculate_perimeter(int length, int width) {
    if (length < 0 || width < 0) {
        return -1;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if ((length > 0 && width > INT_MAX / 2) || (width > 0 && length > INT_MAX / 2)) {
        return -1;
    }

    return 2 * (length + width);
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
    long val = strtol(argv[1], &endptr, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     */
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid length\n");
        return EXIT_FAILURE;
    }
    int length = (int)val;

    val = strtol(argv[2], &endptr, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     */
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        fprintf(stderr, "Invalid width\n");
        return EXIT_FAILURE;
    }
    int width = (int)val;

    int perimeter = calculate_perimeter(length, width);
    if (perimeter < 0) {
        fprintf(stderr, "Calculation error\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", perimeter);

    return EXIT_SUCCESS;
}