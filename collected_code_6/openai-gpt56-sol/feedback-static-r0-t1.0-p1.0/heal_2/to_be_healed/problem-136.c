#include <ctype.h>
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    double units;
    double bill;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[0] == '\0') {
        fputs("Invalid electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    end = input;
    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '\0') {
        fputs("Invalid electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    units = strtod(end, &end);

    if (errno == ERANGE || !isfinite(units)) {
        fputs("Invalid electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        if (*end != '\n') {
            fputs("Invalid electricity usage.\n", stderr);
            return EXIT_FAILURE;
        }

        ++end;
        while (isspace((unsigned char)*end)) {
            ++end;
        }

        if (*end != '\0') {
            fputs("Invalid electricity usage.\n", stderr);
            return EXIT_FAILURE;
        }
    } else if (input[sizeof input - 2] != '\0') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (!calculate_electricity_bill(units, &bill)) {
        fputs("Invalid electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Electricity bill: %.2f\n", bill) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}