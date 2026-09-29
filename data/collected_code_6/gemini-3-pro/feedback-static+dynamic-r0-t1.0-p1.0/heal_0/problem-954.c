#include <stdio.h>
#include <stdlib.h>

#define NO_PROFIT -1.0

double calculate_profit(double cost_price, double selling_price) {
    if (cost_price < 0.0 || selling_price < 0.0) {
        return NO_PROFIT;
    }
    
    if (selling_price > cost_price) {
        return selling_price - cost_price;
    }
    
    return NO_PROFIT;
}

int main(void) {
    double cost = 100.0;
    double selling = 120.0;
    double profit;

    profit = calculate_profit(cost, selling);

    if (profit != NO_PROFIT) {
        printf("Profit amount: %.2f\n", profit);
    } else {
        printf("None\n");
    }

    cost = 150.0;
    selling = 150.0;

    profit = calculate_profit(cost, selling);

    if (profit != NO_PROFIT) {
        printf("Profit amount: %.2f\n", profit);
    } else {
        printf("None\n");
    }

    cost = 200.0;
    selling = 180.0;

    profit = calculate_profit(cost, selling);

    if (profit != NO_PROFIT) {
        printf("Profit amount: %.2f\n", profit);
    } else {
        printf("None\n");
    }

    return EXIT_SUCCESS;
}