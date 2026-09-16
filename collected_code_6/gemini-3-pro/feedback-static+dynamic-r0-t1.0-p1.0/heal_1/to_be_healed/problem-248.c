#include <stdio.h>
#include <stdlib.h>

double harmonic_sum_n_minus_one(int n) {
    double sum = 0.0;

    if (n <= 1) {
        return 0.0;
    }

    for (int i = 1; i < n; i++) {
        sum += 1.0 / (double)i;
    }

    return sum;
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'n=5', assigned value is 5
     */
    int n = 5;
    /* Possible weaknesses found:
     *  Variable 'result' is assigned a value that is never used. [unreadVariable]
     *  The scope of the variable 'result' can be reduced. [variableScope]
     */
    double result = 0.0;

    /* Possible weaknesses found:
     *  Condition 'n>1' is always true
     *  Condition 'n>1' is always true [knownConditionTrueFalse]
     */
    if (n > 1) {
        result = harmonic_sum_n_minus_one(n);
        printf("%.6f\n", result);
    } else {
        printf("0.000000\n");
    }

    return EXIT_SUCCESS;
}