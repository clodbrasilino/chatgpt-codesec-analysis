#include <stdio.h>
#include <stdlib.h>

double harmonic_sum_n_minus_one(int n) {
    if (n <= 1) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 1; i < n; i++) {
        sum += 1.0 / (double)i;
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n = 5;
    
    if (argc > 1) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        n = atoi(argv[1]);
    }

    if (n > 1) {
        double result = harmonic_sum_n_minus_one(n);
        printf("%.6f\n", result);
    } else {
        printf("0.000000\n");
    }

    return EXIT_SUCCESS;
}