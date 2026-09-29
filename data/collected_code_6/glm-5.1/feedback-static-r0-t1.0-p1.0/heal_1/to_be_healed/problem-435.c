#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int find_last_digit(int n) {
    int abs_n;
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MIN' undeclared (first use in this function)
     */
    if (n == INT_MIN) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         *  'INT_MAX' undeclared (first use in this function)
         *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         */
        abs_n = INT_MAX + 1;
    } else if (n < 0) {
        abs_n = -n;
    } else {
        abs_n = n;
    }
    return abs_n % 10;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    int last_digit = find_last_digit(n);
    printf("%d\n", last_digit);
    return EXIT_SUCCESS;
}