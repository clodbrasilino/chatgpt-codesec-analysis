#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int calculate_electricity_bill(double units, double *bill)
{
    if (bill == NULL || !isfinite(units) || units < 0.0) {
        return -1;
    }

    if (units <= 100.0) {
        *bill = units * 1.50;
    } else if (units <= 200.0) {
        *bill = 150.0 + (units - 100.0) * 2.50;
    } else if (units <= 500.0) {
        *bill = 400.0 + (units - 200.0) * 4.00;
    } else {
        *bill = 1600.0 + (units - 500.0) * 6.00;
    }

    return isfinite(*bill) ? 0 : -1;
}

int main(void)
{
    char input[256];
    char *end;
    double units;
    double bill;

    if (fputs("Enter electricity usage in kWh: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL) {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    units = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
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