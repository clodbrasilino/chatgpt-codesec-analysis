#include <stdio.h>
#include <stdlib.h>

static int has_no_profit_no_loss(double cost_price, double selling_price)
{
    return cost_price == selling_price;
}

int main(void)
{
    double cost_price;
    double selling_price;

    if (scanf("%lf %lf", &cost_price, &selling_price) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (cost_price < 0.0 || selling_price < 0.0) {
        fputs("Amounts must be non-negative\n", stderr);
        return EXIT_FAILURE;
    }

    if (has_no_profit_no_loss(cost_price, selling_price)) {
        puts("No profit and no loss");
    } else if (selling_price > cost_price) {
        puts("Profit");
    } else {
        puts("Loss");
    }

    return EXIT_SUCCESS;
}