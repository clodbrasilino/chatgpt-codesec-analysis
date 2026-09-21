#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>

static int calculate_profit(double cost, double revenue, double *profit)
{
    double result;

    if (profit == NULL ||
        !isfinite(cost) ||
        !isfinite(revenue) ||
        cost < 0.0 ||
        revenue < 0.0 ||
        revenue <= cost) {
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
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *cursor;
    char *end;
    double parsed_cost;
    double parsed_revenue;

    if (cost == NULL || revenue == NULL) {
        return 0;
    }

    errno = 0;
    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    while (length > 0 &&
           (line[length - 1] == '\n' || line[length - 1] == '\r')) {
        line[--length] = '\0';
    }

    cursor = line;
    errno = 0;
    parsed_cost = strtod(cursor, &end);
    if (end == cursor || errno == ERANGE) {
        free(line);
        return 0;
    }

    cursor = end;
    errno = 0;
    parsed_revenue = strtod(cursor, &end);
    if (end == cursor || errno == ERANGE) {
        free(line);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *cost = parsed_cost;
    *revenue = parsed_revenue;
    free(line);
    return 1;
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