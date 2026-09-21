#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_electricity_bill(double units, double *bill)
{
    double result;

    if (bill == NULL || !isfinite(units) || units < 0.0) {
        return -1;
    }

    if (units <= 100.0) {
        result = units * 1.50;
    } else if (units <= 200.0) {
        result = 150.0 + (units - 100.0) * 2.50;
    } else if (units <= 500.0) {
        result = 400.0 + (units - 200.0) * 4.00;
    } else {
        result = 1600.0 + (units - 500.0) * 6.00;
    }

    if (!isfinite(result)) {
        return -1;
    }

    *bill = result;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double units;
    double bill;

    if (printf("Enter electricity usage in kWh: ") < 0) {
        return EXIT_FAILURE;
    }

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        fputs("Failed to read input.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    units = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid electricity usage.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid electricity usage.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (calculate_electricity_bill(units, &bill) != 0) {
        fputs("Electricity usage is outside the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Electricity bill: %.2f\n", bill) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}