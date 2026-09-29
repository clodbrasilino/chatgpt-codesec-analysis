#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>

static int calculate_profit(double cost, double revenue, double *profit)
{
    double result;

    if (profit == NULL || !isfinite(cost) || !isfinite(revenue) ||
        cost < 0.0 || revenue < 0.0 || revenue <= cost) {
        return 0;
    }

    result = revenue - cost;
    if (!isfinite(result)) {
        return 0;
    }

    *profit = result;
    return 1;
}

static int read_values(double *cost, double *revenue)
{
    char input[256];
    char *cursor;
    char *end;
    size_t length;
    int ch;

    if (cost == NULL || revenue == NULL) {
        return 0;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input) {
        return 0;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (!feof(stdin)) {
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }
        return 0;
    }

    cursor = input;
    errno = 0;
    *cost = strtod(cursor, &end);
    if (end == cursor || errno == ERANGE) {
        return 0;
    }

    cursor = end;
    errno = 0;
    *revenue = strtod(cursor, &end);
    if (end == cursor || errno == ERANGE) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    return *end == '\0';
}

int main(void)
{
    double cost;
    double revenue;
    double profit;

    if (!read_values(&cost, &revenue)) {
        return EXIT_FAILURE;
    }

    if (calculate_profit(cost, revenue, &profit)) {
        if (printf("%.2f\n", profit) < 0) {
            return EXIT_FAILURE;
        }
    } else if (puts("none") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}