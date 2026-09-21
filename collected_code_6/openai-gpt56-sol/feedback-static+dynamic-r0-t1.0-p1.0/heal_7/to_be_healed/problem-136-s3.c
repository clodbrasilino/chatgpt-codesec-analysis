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

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || feof(stdin);
}

static int read_line(char **line)
{
    char *buffer;
    size_t length;
    size_t capacity = (size_t)MAX_INPUT_LENGTH + 2U;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        free(buffer);
        return 0;
    }

    for (length = 0; buffer[length] != '\0' && buffer[length] != '\n'; ++length) {
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (length > (size_t)MAX_INPUT_LENGTH) {
        if (!discard_line()) {
            free(buffer);
            return 0;
        }

        free(buffer);
        return 0;
    } else {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            if (!discard_line()) {
                free(buffer);
                return 0;
            }

            free(buffer);
            return 0;
        }
    }

    if (length > 0U && buffer[length - 1U] == '\r') {
        buffer[length - 1U] = '\0';
    }

    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    double units;
    double bill;

    if (!read_line(&input)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    units = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(units)) {
        free(input);
        fputs("Invalid electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid electricity usage.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!calculate_electricity_bill(units, &bill)) {
        fputs("Unable to calculate the electricity bill.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Electricity bill: %.2f\n", bill) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}