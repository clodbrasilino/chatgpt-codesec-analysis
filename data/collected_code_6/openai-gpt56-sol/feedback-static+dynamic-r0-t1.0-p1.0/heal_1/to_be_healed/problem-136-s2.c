#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_electricity_bill(double units, double *bill)
{
    if (bill == NULL || !isfinite(units) || units < 0.0) {
        return -1;
    }

    if (units <= 100.0) {
        *bill = units * 1.50;
    } else if (units <= 200.0) {
        *bill = 100.0 * 1.50 + (units - 100.0) * 2.50;
    } else if (units <= 500.0) {
        *bill = 100.0 * 1.50 + 100.0 * 2.50 + (units - 200.0) * 4.00;
    } else {
        *bill = 100.0 * 1.50 + 100.0 * 2.50 + 300.0 * 4.00
              + (units - 500.0) * 6.00;
    }

    return isfinite(*bill) ? 0 : -1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end = NULL;
    double units;
    double bill;

    if (printf("Enter electricity usage in kWh: ") < 0) {
        return EXIT_FAILURE;
    }

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

    if (calculate_electricity_bill(units, &bill) != 0) {
        fputs("Electricity usage is outside the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Electricity bill: %.2f\n", bill) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}