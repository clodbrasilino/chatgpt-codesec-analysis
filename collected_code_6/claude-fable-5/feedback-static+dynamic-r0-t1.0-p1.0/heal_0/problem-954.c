#include <stdio.h>
#include <stdlib.h>

int calculate_profit(double cost_price, double selling_price, double *profit)
{
    if (profit == NULL) {
        return -1;
    }
    if (cost_price < 0.0 || selling_price < 0.0) {
        return -1;
    }
    if (selling_price > cost_price) {
        *profit = selling_price - cost_price;
        return 0;
    }
    return 1;
}

int main(void)
{
    double cost_price = 0.0;
    double selling_price = 0.0;
    double profit = 0.0;
    int result = 0;

    printf("Enter cost price: ");
    if (scanf("%lf", &cost_price) != 1) {
        fprintf(stderr, "Invalid input for cost price\n");
        return EXIT_FAILURE;
    }

    printf("Enter selling price: ");
    if (scanf("%lf", &selling_price) != 1) {
        fprintf(stderr, "Invalid input for selling price\n");
        return EXIT_FAILURE;
    }

    result = calculate_profit(cost_price, selling_price, &profit);

    if (result < 0) {
        fprintf(stderr, "Invalid values provided\n");
        return EXIT_FAILURE;
    }

    if (result == 0) {
        printf("Profit: %.2f\n", profit);
    } else {
        printf("None\n");
    }

    return EXIT_SUCCESS;
}