#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int find_closest_smaller(int n) {
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MIN' undeclared (first use in this function)
     */
    if (n > INT_MIN) {
        return n - 1;
    }
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    int n;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    n = atoi(argv[1]);
    int result = find_closest_smaller(n);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}