#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 4096 };

static int calculate_electricity_bill(double units, double *bill)
{
    double result;

    if (bill == NULL || !isfinite(units) || units < 0.0) {
        return 0;
    }

    if (units <= 100.0) {
        result = units * 0.50;
    } else if (units <= 200.0) {
        result = 50.0 + (units - 100.0) * 0.75;
    } else if (units <= 300.0) {
        result = 125.0 + (units - 200.0) * 1.20;
    } else {
        result = 245.0 + (units - 300.0) * 1.50;
    }

    if (!isfinite(result)) {
        return 0;
    }

    *bill = result;
    return 1;
}

static int discard_line_remainder(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || !ferror(stdin);
}

static int read_line(char *buffer, size_t capacity)
{
    size_t length = 0U;
    int ch;

    if (buffer == NULL || capacity < 2U) {
        return 0;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1U >= capacity) {
            buffer[0] = '\0';
            if (!discard_line_remainder()) {
                return 0;
            }
            return 0;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        buffer[0] = '\0';
        return 0;
    }

    if (ch == EOF && length == 0U) {
        buffer[0] = '\0';
        return 0;
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        --length;
    }

    buffer[length] = '\0';
    return 1;
}

int main(void)
{
    char input[MAX_INPUT_LENGTH + 1U];
    char *end;
    double units;
    double bill;

    if (!read_line(input, sizeof input)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    units = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(units)) {
        fputs("Invalid electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
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