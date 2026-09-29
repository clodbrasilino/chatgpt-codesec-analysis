#include <stdio.h>
#include <stdlib.h>

static double calculate_loss(double cost_price, double selling_price)
{
    return cost_price > selling_price ? cost_price - selling_price : 0.0;
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
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    const double loss = calculate_loss(cost_price, selling_price);

    if (loss > 0.0) {
        printf("%.2f\n", loss);
    } else {
        puts("none");
    }

    return EXIT_SUCCESS;
}