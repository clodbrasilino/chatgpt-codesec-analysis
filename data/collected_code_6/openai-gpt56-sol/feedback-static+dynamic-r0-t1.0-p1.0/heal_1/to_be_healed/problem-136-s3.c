#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_electricity_bill(double units, double *bill)
{
    if (bill == NULL || !isfinite(units) || units < 0.0) {
        return 0;
    }

    if (units <= 100.0) {
        *bill = units * 0.50;
    } else if (units <= 200.0) {
        *bill = 100.0 * 0.50 + (units - 100.0) * 0.75;
    } else if (units <= 300.0) {
        *bill = 100.0 * 0.50 + 100.0 * 0.75 + (units - 200.0) * 1.20;
    } else {
        *bill = 100.0 * 0.50 + 100.0 * 0.75 + 100.0 * 1.20
              + (units - 300.0) * 1.50;
    }

    return isfinite(*bill);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end = NULL;
    double units;
    double bill;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    units = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        fputs("Invalid electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_electricity_bill(units, &bill)) {
        fputs("Unable to calculate the electricity bill.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Electricity bill: %.2f\n", bill) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}