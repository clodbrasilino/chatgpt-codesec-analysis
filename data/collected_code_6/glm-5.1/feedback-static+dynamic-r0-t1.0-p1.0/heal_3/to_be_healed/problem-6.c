#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int differ_at_one_bit_position(int a, int b) {
    int xor_result = a ^ b;
    if (xor_result == 0) {
        return 0;
    }
    if ((xor_result & (xor_result - 1)) == 0) {
        return 1;
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int1> <int2>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr1, *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);
    /* Possible weaknesses found:
     *  'INT_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MIN' undeclared (first use in this function)
     *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'INT_MIN'
     */
    if (*endptr1 != '\0' || *endptr2 != '\0' || val1 < INT_MIN || val1 > INT_MAX || val2 < INT_MIN || val2 > INT_MAX) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }
    int res = differ_at_one_bit_position((int)val1, (int)val2);
    printf("%s\n", res ? "True" : "False");
    return EXIT_SUCCESS;
}