#include <stdio.h>
#include <stdbool.h>

bool is_no_profit_no_loss(double cost_price, double selling_price) {
    return cost_price == selling_price;
}

int main(void) {
    double cost_price, selling_price;

    printf("Enter the cost price: ");
    if (scanf("%lf", &cost_price) != 1) {
        fprintf(stderr, "Invalid input for cost price.\n");
        return 1;
    }

    printf("Enter the selling price: ");
    if (scanf("%lf", &selling_price) != 1) {
        fprintf(stderr, "Invalid input for selling price.\n");
        return 1;
    }

    if (is_no_profit_no_loss(cost_price, selling_price)) {
        printf("No profit, no loss.\n");
    } else {
        printf("There is either profit or loss.\n");
    }

    return 0;
}