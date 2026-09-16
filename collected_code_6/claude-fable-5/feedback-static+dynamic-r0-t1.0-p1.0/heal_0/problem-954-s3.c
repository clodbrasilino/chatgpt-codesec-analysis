#include <stdio.h>
#include <stdbool.h>

bool calculate_profit(double cost_price, double selling_price, double *profit)
{
    if (profit == NULL) {
        return false;
    }

    if (selling_price > cost_price) {
        *profit = selling_price - cost_price;
        return true;
    }

    return false;
}

int main(void)
{
    double cost_price;
    double selling_price;
    double profit;

    printf("Enter cost price: ");
    if (scanf("%lf", &cost_price) != 1) {
        fprintf(stderr, "Invalid input for cost price\n");
        return 1;
    }

    printf("Enter selling price: ");
    if (scanf("%lf", &selling_price) != 1) {
        fprintf(stderr, "Invalid input for selling price\n");
        return 1;
    }

    if (cost_price < 0.0 || selling_price < 0.0) {
        fprintf(stderr, "Prices must be non-negative\n");
        return 1;
    }

    if (calculate_profit(cost_price, selling_price, &profit)) {
        printf("Profit: %.2f\n", profit);
    } else {
        printf("None\n");
    }

    return 0;
}