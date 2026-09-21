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
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    char *end = NULL;
    double units;
    double bill;
    int status = EXIT_FAILURE;
    int ch;

    if (fputs("Enter electricity usage in kWh: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;
        size_t new_capacity;

        if (length == SIZE_MAX - 1) {
            fputs("Input is too long.\n", stderr);
            goto cleanup;
        }

        if (length + 1 >= capacity) {
            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    fputs("Input is too long.\n", stderr);
                    goto cleanup;
                }
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                fputs("Unable to allocate memory.\n", stderr);
                goto cleanup;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        goto cleanup;
    }

    if (length == 0 && ch == EOF) {
        fputs("Failed to read input.\n", stderr);
        goto cleanup;
    }

    if (length + 1 > capacity) {
        char *resized = realloc(input, length + 1);

        if (resized == NULL) {
            fputs("Unable to allocate memory.\n", stderr);
            goto cleanup;
        }

        input = resized;
        capacity = length + 1;
    }

    input[length] = '\0';

    errno = 0;
    units = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid electricity usage.\n", stderr);
        goto cleanup;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid electricity usage.\n", stderr);
        goto cleanup;
    }

    if (calculate_electricity_bill(units, &bill) != 0) {
        fputs("Electricity usage is outside the supported range.\n", stderr);
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