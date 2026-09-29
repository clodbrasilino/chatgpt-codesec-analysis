#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

int is_perfect_square(long long num) {
    if (num < 0) {
        return 0;
    }
    if (num == 0) {
        return 1;
    }
    long long root = (long long)round(sqrt((double)num));
    if (root * root == num) {
        return 1;
    }
    root++;
    if (root * root == num) {
        return 1;
    }
    root -= 2;
    if (root * root == num) {
        return 1;
    }
    return 0;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return 1;
    }
    if (argv[1][0] == '\0') {
        return 1;
    }
    char *endptr;
    /* Possible weaknesses found:
     *  'errno' undeclared (first use in this function)
     *  use of undeclared identifier 'errno'
     *  each undeclared identifier is reported only once for each function it appears in
     */
    errno = 0;
    long long val = strtoll(argv[1], &endptr, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'errno'
     */
    if (errno != 0 || *endptr != '\0') {
        return 1;
    }
    int result = is_perfect_square(val);
    if (result) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return 0;
}