#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double geometric_series_sum(double first_term, double common_ratio, int terms) {
    if (terms <= 0) {
        return 0.0;
    }
    if (common_ratio == 1.0) {
        return first_term * terms;
    }
    return first_term * (1.0 - pow(common_ratio, terms)) / (1.0 - common_ratio);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    double first_term, common_ratio, sum;
    int terms;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <first_term> <common_ratio> <terms>\n", argv[0]);
        return EXIT_FAILURE;
    }

    first_term = strtod(argv[1], NULL);
    common_ratio = strtod(argv[2], NULL);
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    terms = atoi(argv[3]);

    if (terms <= 0) {
        fprintf(stderr, "Error: Number of terms must be positive.\n");
        return EXIT_FAILURE;
    }

    sum = geometric_series_sum(first_term, common_ratio, terms);
    printf("Sum of geometric series: %.10f\n", sum);

    return EXIT_SUCCESS;
}