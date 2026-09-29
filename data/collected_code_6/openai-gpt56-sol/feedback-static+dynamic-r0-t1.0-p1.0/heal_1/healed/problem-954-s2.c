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

static int discard_line(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == '\n';
}

static int read_amount(const char *prompt, double *amount)
{
    char buffer[128];
    char *end;
    double value;
    size_t length;

    if (prompt == NULL || amount == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (length < sizeof buffer && buffer[length] != '\0') {
        ++length;
    }

    if (length == sizeof buffer) {
        return 0;
    }

    if (length == sizeof buffer - 1 && buffer[length - 1] != '\n') {
        discard_line();
        return 0;
    }

    errno = 0;
    end = NULL;
    value = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(value) ||
        value < 0.0) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
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