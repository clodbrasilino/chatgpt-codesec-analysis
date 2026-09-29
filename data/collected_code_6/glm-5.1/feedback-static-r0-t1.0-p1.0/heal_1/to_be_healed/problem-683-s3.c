#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

bool canBeSumOfTwoSquares(int n) {
    if (n < 0) {
        return false;
    }
    long long limit = (long long)sqrt((double)n);
    for (long long a = 0; a <= limit; a++) {
        long long b_squared = (long long)n - a * a;
        if (b_squared < 0) {
            break;
        }
        long long b = (long long)sqrt((double)b_squared);
        if (b * b == b_squared) {
            return true;
        }
    }
    return false;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MIN' undeclared (first use in this function)
     *  use of undeclared identifier 'INT_MAX'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  'INT_MAX' undeclared (first use in this function)
     */
    if (endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid input: Not a valid integer\n");
        return EXIT_FAILURE;
    }
    if (canBeSumOfTwoSquares((int)val)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return EXIT_SUCCESS;
}