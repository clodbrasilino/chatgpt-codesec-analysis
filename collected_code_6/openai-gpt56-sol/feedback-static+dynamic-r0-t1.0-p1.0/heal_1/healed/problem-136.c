#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_electricity_bill(double units, double *bill)
{
    double amount;

    if (bill == NULL || !isfinite(units) || units < 0.0) {
        return 0;
    }

    if (units <= 100.0) {
        amount = units * 1.50;
    } else if (units <= 200.0) {
        amount = 100.0 * 1.50 + (units - 100.0) * 2.50;
    } else if (units <= 500.0) {
        amount = 100.0 * 1.50
               + 100.0 * 2.50
               + (units - 200.0) * 4.00;
    } else {
        amount = 100.0 * 1.50
               + 100.0 * 2.50
               + 300.0 * 4.00
               + (units - 500.0) * 6.00;
    }

    if (!isfinite(amount)) {
        return 0;
    }

    *bill = amount;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double units;
    double bill;
    int status = EXIT_FAILURE;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        fputs("Failed to read electricity usage.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    units = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid electricity usage.\n", stderr);
        goto cleanup;
    }

    while (*end == ' ' || *end == '\t' ||
           *end == '\r' || *end == '\n' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0' || !calculate_electricity_bill(units, &bill)) {
        fputs("Invalid electricity usage.\n", stderr);
        goto cleanup;
    }

    if (printf("Electricity bill: %.2f\n", bill) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}