#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

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

int main(void)
{
    char input[256];
    char *end;
    char *start;
    double cost;
    double revenue;
    double profit;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    errno = 0;
    start = input;
    cost = strtod(start, &end);
    if (end == start || errno == ERANGE || !isfinite(cost)) {
        return EXIT_FAILURE;
    }

    errno = 0;
    start = end;
    revenue = strtod(start, &end);
    if (end == start || errno == ERANGE || !isfinite(revenue)) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (calculate_profit(cost, revenue, &profit)) {
        if (printf("%.2f\n", profit) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (puts("none") == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}