#include <stdio.h>
#include <stdlib.h>

static int calculate_profit(double cost, double selling_price, double *profit)
{
    if (profit == NULL || cost < 0.0 || selling_price < 0.0 || selling_price <= cost) {
        return 0;
    }

    *profit = selling_price - cost;
    return 1;
}

int main(void)
{
    double cost;
    double selling_price;
    double profit;

    if (scanf("%lf %lf", &cost, &selling_price) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_profit(cost, selling_price, &profit)) {
        printf("%.2f\n", profit);
    } else {
        puts("none");
    }

    return EXIT_SUCCESS;
}