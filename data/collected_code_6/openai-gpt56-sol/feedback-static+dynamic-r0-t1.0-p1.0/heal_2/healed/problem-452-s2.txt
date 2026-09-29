#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
#include <stdint.h>

static int calculate_loss(double cost_price, double selling_price, double *loss)
{
    if (loss == NULL ||
        !isfinite(cost_price) ||
        !isfinite(selling_price) ||
        cost_price < 0.0 ||
        selling_price < 0.0) {
        return 0;
    }

    if (cost_price > selling_price) {
        *loss = cost_price - selling_price;
        return 1;
    }

    *loss = 0.0;
    return 0;
}

static int read_amount(const char *prompt, double *amount)
{
    char buffer[256];
    char *end;
    double value;
    int ch;

    if (prompt == NULL || amount == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    if (strchr(buffer, '\n') == NULL) {
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }
        return 0;
    }

    errno = 0;
    end = buffer;
    value = strtod(buffer, &end);

    if (end == buffer ||
        errno == ERANGE ||
        !isfinite(value) ||
        value < 0.0) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
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
    double cost_price;
    double selling_price;
    double loss;

    if (!read_amount("Enter cost price: ", &cost_price) ||
        !read_amount("Enter selling price: ", &selling_price)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_loss(cost_price, selling_price, &loss)) {
        printf("Loss amount: %.2f\n", loss);
    } else {
        puts("None");
    }

    return EXIT_SUCCESS;
}