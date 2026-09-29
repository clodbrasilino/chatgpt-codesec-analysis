#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int hamming_distance(int x, int y) {
    unsigned int xor_val = (unsigned int)x ^ (unsigned int)y;
    int distance = 0;
    while (xor_val) {
        distance += xor_val & 1;
        xor_val >>= 1;
    }
    return distance;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int1> <int2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1, *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);

    if (*endptr1 != '\0' || *endptr2 != '\0') {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MIN' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  'INT_MAX' undeclared (first use in this function)
     */
    if (val1 < INT_MIN || val1 > INT_MAX || val2 < INT_MIN || val2 > INT_MAX) {
        fprintf(stderr, "Integer overflow\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", hamming_distance((int)val1, (int)val2));

    return EXIT_SUCCESS;
}