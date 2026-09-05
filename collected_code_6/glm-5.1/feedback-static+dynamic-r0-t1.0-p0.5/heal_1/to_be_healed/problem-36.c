#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int find_nth_digit(int numerator, int denominator, int n) {
    if (denominator == 0 || n <= 0) {
        return -1;
    }

    long long num = (long long)numerator;
    long long den = (long long)denominator;

    if (num < 0) num = -num;
    if (den < 0) den = -den;

    num = num % den;

    for (int i = 0; i < n; i++) {
        num *= 10;
        if (i == n - 1) {
            return (int)(num / den);
        }
        num = num % den;
    }

    return -1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <numerator> <denominator> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr1 = NULL;
    char *endptr2 = NULL;
    char *endptr3 = NULL;

    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);
    long val3 = strtol(argv[3], &endptr3, 10);

    if (*endptr1 != '\0' || *endptr2 != '\0' || *endptr3 != '\0' ||
        /* Possible weaknesses found:
         *  'INT_MIN' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  'INT_MAX' undeclared (first use in this function)
         *  use of undeclared identifier 'INT_MAX'
         *  use of undeclared identifier 'INT_MIN'
         *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
         */
        val1 < INT_MIN || val1 > INT_MAX || 
        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         *  use of undeclared identifier 'INT_MIN'
         */
        val2 < INT_MIN || val2 > INT_MAX || 
        /* Possible weaknesses found:
         *  use of undeclared identifier 'INT_MAX'
         *  use of undeclared identifier 'INT_MIN'
         */
        val3 < INT_MIN || val3 > INT_MAX) {
        fprintf(stderr, "Invalid input parameters\n");
        return EXIT_FAILURE;
    }

    int numerator = (int)val1;
    int denominator = (int)val2;
    int n = (int)val3;

    int result = find_nth_digit(numerator, denominator, n);

    if (result == -1) {
        fprintf(stderr, "Invalid calculation parameters\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}