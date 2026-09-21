#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

static int calculate_loss(double cost_price, double selling_price, double *loss)
{
    if (loss == NULL || !isfinite(cost_price) || !isfinite(selling_price) ||
        cost_price < 0.0 || selling_price < 0.0) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end = NULL;
    double value;

    if (prompt == NULL || amount == NULL) {
        return 0;
    }

    fputs(prompt, stdout);
    if (fflush(stdout) == EOF || fgets(buffer, sizeof buffer, stdin) == NULL) {
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