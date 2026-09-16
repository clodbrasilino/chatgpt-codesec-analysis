#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double round_up_digits(double number, int digits) {
    if (digits < 0) {
        return number;
    }
    if (digits == 0) {
        return ceil(number);
    }
    int max_digits = 15;
    if (digits > max_digits) {
        digits = max_digits;
    }
    double factor = pow(10.0, (double)digits);
    if (factor == 0.0) {
        return number;
    }
    double scaled = number * factor;
    if (scaled == 0.0 || isinf(scaled) || isnan(scaled)) {
        return number;
    }
    double shifted = ceil(scaled);
    return shifted / factor;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    char *endptr;
    double number = strtod(argv[1], &endptr);
    if (endptr == argv[1]) {
        return EXIT_FAILURE;
    }
    long digits_long = strtol(argv[2], &endptr, 10);
    if (endptr == argv[2] || digits_long < 0 || digits_long > 15) {
        return EXIT_FAILURE;
    }
    int digits = (int)digits_long;
    double result = round_up_digits(number, digits);
    printf("%.*f\n", digits, result);
    return EXIT_SUCCESS;
}