#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>

static int calculate_loss(double cost_price, double selling_price, double *loss)
{
    if (loss == NULL ||
        !isfinite(cost_price) ||
        !isfinite(selling_price) ||
        cost_price < 0.0 ||
        selling_price < 0.0) {
        return 0;
    }

    *loss = cost_price > selling_price
        ? cost_price - selling_price
        : 0.0;

    return cost_price > selling_price;
}

static int read_amount(const char *prompt, double *amount)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double value;

    if (prompt == NULL || amount == NULL) {
        return 0;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    errno = 0;
    end = NULL;
    value = strtod(line, &end);

    if (end == line || errno == ERANGE || !isfinite(value) || value < 0.0) {
        free(line);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *amount = value;
    free(line);
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