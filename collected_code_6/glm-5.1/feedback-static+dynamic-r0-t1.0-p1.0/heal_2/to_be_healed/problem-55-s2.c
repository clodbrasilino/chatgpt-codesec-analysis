#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

double geometric_term(double a, double r, int n) {
    /* Possible weaknesses found:
     *  Assuming that condition 'n<=0' is not redundant
     */
    if (n <= 0) {
        return 0.0;
    }
    double result = 1.0;
    /* Possible weaknesses found:
     *  Assignment 'exp=n-1', assigned value is greater than -1
     */
    int exp = n - 1;
    double base = r;
    if (base < 0 && exp % 2 != 0) {
        base = -base;
        result = -1.0;
    } else if (base < 0) {
        base = -base;
        result = 1.0;
    }
    /* Possible weaknesses found:
     *  Condition 'exp<0' is always false
     *  Condition 'exp<0' is always false [knownConditionTrueFalse]
     */
    if (exp < 0) {
        base = 1.0 / base;
        exp = -exp;
    }
    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return a * result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <common_ratio> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    double a = atof(argv[1]);
    double r = atof(argv[2]);
    long n_long = strtol(argv[3], NULL, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  'INT_MAX' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    if (n_long <= 0 || n_long > INT_MAX) {
        fprintf(stderr, "Error: n must be a positive integer\n");
        return EXIT_FAILURE;
    }
    int n = (int)n_long;
    double term = geometric_term(a, r, n);
    printf("%f\n", term);
    return EXIT_SUCCESS;
}