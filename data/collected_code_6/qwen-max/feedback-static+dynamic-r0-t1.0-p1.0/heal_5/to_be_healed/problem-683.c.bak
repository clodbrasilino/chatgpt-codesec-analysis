#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  'errno' is defined in header '<errno.h>'; this is probably fixable by adding '#include <errno.h>'
  */

int isSumOfTwoSquares(long n) {
    if (n < 0)
        return 0;
    for (long i = 0; i * i <= n; ++i) {
        long j = lround(sqrt(n - i * i));
        if (i * i + j * j == n && j * j == (n - i * i)) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char input[256];
    printf("Enter a number: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        char *endptr;
        /* Possible weaknesses found:
         *  use of undeclared identifier 'errno'
         *  'errno' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         */
        errno = 0;
        long n = strtol(input, &endptr, 10);
        /* Possible weaknesses found:
         *  'ERANGE' undeclared (first use in this function)
         *  use of undeclared identifier 'errno'
         *  use of undeclared identifier 'ERANGE'
         */
        if (errno == ERANGE || *endptr != '\n' || endptr == input) {
            printf("Invalid input.\n");
            return 1;
        }
        if (isSumOfTwoSquares(n)) {
            printf("The number can be represented as the sum of two squares.\n");
        } else {
            printf("The number cannot be represented as the sum of two squares.\n");
        }
    } else {
        printf("Error reading input.\n");
        return 1;
    }
    return 0;
}