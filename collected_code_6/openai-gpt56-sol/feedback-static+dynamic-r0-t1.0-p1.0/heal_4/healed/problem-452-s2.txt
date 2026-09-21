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

static int discard_line(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == '\n';
}

static int read_amount(const char *prompt, double *amount)
{
    char buffer[256];
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

    for (length = 0; length < sizeof buffer && buffer[length] != '\0'; ++length) {
    }

    if (length == 0 || length == sizeof buffer) {
        return 0;
    }

    if (buffer[length - 1] != '\n' && !feof(stdin)) {
        discard_line();
        return 0;
    }

    errno = 0;
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
    double cost_price;
    double selling_price;
    double loss;

    if (!read_amount("Enter cost price: ", &cost_price) ||
        !read_amount("Enter selling price: ", &selling_price)) {
        if (fputs("Invalid input.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (calculate_loss(cost_price, selling_price, &loss)) {
        if (printf("Loss amount: %.2f\n", loss) < 0) {
            return EXIT_FAILURE;
        }
    } else if (puts("None") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}