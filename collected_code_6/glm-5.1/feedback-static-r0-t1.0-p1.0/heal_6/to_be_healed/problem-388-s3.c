#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

unsigned int highest_power_of_2(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n - (n >> 1);
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (argv[1][0] == '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    char *endptr;
    /* Possible weaknesses found:
     *  use of undeclared identifier 'errno'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'errno' undeclared (first use in this function)
     */
    errno = 0;
    unsigned long val = strtoul(argv[1], &endptr, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'errno'
     *  'ERANGE' undeclared (first use in this function)
     *  use of undeclared identifier 'ERANGE'
     */
    if (*endptr != '\0' || errno == ERANGE || val > UINT_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    unsigned int result = highest_power_of_2((unsigned int)val);
    printf("%u\n", result);
    return EXIT_SUCCESS;
}