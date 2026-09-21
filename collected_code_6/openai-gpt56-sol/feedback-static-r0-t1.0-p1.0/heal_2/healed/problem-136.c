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
        amount = 150.0 + (units - 100.0) * 2.50;
    } else if (units <= 500.0) {
        amount = 400.0 + (units - 200.0) * 4.00;
    } else {
        amount = 1600.0 + (units - 500.0) * 6.00;
    }

    if (!isfinite(amount)) {
        return 0;
    }

    *bill = amount;
    return 1;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *start;
    char *end;
    double units;
    double bill;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        fputs("Failed to read electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    start = line;
    while (*start == ' ' || *start == '\t' || *start == '\n' ||
           *start == '\r' || *start == '\f' || *start == '\v') {
        ++start;
    }

    if (*start == '\0') {
        free(line);
        fputs("Invalid electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    units = strtod(start, &end);

    if (start == end || errno == ERANGE || !isfinite(units)) {
        free(line);
        fputs("Invalid electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        fputs("Invalid electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_electricity_bill(units, &bill)) {
        free(line);
        fputs("Invalid electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);

    if (printf("Electricity bill: %.2f\n", bill) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}