#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

static int calculate_profit(double cost, double revenue, double *profit)
{
    if (profit == NULL || !isfinite(cost) || !isfinite(revenue) ||
        cost < 0.0 || revenue < 0.0 || revenue <= cost) {
        return 0;
    }

    *profit = revenue - cost;
    return isfinite(*profit);
}

static int read_amount(const char *prompt, double *amount)
{
    char buffer[128];
    char *end = NULL;
    double value;

    if (prompt == NULL || amount == NULL) {
        return 0;
    }

    fputs(prompt, stdout);

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    value = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(value) || value < 0.0) {
        return 0;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return 0;
    }

    *amount = value;
    return 1;
}

int main(void)
{
    double cost;
    double revenue;
    double profit;

    if (!read_amount("Enter cost amount: ", &cost) ||
        !read_amount("Enter selling amount: ", &revenue)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_profit(cost, revenue, &profit)) {
        printf("Profit: %.2f\n", profit);
    } else {
        puts("none");
    }

    return EXIT_SUCCESS;
}