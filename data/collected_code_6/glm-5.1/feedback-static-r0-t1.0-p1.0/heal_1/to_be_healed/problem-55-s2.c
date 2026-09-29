#include <stdio.h>
#include <stdlib.h>

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
    /* Possible weaknesses found:
     *  Condition 'exp<0' is always false
     *  Condition 'exp<0' is always false [knownConditionTrueFalse]
     */
    if (exp < 0) {
        base = 1.0 / r;
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
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <common_ratio> <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    double a = atof(argv[1]);
    double r = atof(argv[2]);
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int n = atoi(argv[3]);
    if (n <= 0) {
        fprintf(stderr, "Error: n must be a positive integer\n");
        return EXIT_FAILURE;
    }
    double term = geometric_term(a, r, n);
    printf("%f\n", term);
    return EXIT_SUCCESS;
}