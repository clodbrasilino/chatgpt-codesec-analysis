#include <ctype.h>
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
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double units;
    double bill;

    if (fputs("Enter electricity usage in kWh: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    errno = 0;
    length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    errno = 0;
    units = strtod(line, &end);

    if (end == line || errno == ERANGE) {
        free(line);
        fputs("Invalid electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        fputs("Invalid electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);

    if (calculate_electricity_bill(units, &bill) != 0) {
        fputs("Electricity usage is outside the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Electricity bill: %.2f\n", bill) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}