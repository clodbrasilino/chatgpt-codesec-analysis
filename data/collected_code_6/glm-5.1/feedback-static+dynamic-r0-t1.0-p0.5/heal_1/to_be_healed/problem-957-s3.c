#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int get_rightmost_set_bit(int n) {
    if (n == 0) {
        return -1;
    }
    return n & (-n);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }

    long val = strtol(argv[1], NULL, 10);
    /* Possible weaknesses found:
     *  'INT_MIN' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     */
    if (val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }

    int n = (int)val;
    int pos = get_rightmost_set_bit(n);

    printf("%d\n", pos);

    return EXIT_SUCCESS;
}