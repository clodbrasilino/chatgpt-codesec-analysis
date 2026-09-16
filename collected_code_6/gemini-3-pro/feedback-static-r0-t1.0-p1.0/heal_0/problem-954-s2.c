#include <stdio.h>
#include <stdlib.h>

int has_profit(double cost_price, double selling_price, double *profit) {
    if (profit == NULL) {
        return 0;
    }
    if (cost_price < 0.0 || selling_price < 0.0) {
        return 0;
    }
    if (selling_price > cost_price) {
        *profit = selling_price - cost_price;
        return 1;
    }
    return 0;
}

int main(void) {
    double cost_price = 100.0;
    double selling_price = 150.0;
    double profit = 0.0;

    if (has_profit(cost_price, selling_price, &profit)) {
        printf("Profit amount: %.2f\n", profit);
    } else {
        printf("None\n");
    }

    cost_price = 200.0;
    selling_price = 150.0;
    profit = 0.0;

    if (has_profit(cost_price, selling_price, &profit)) {
        printf("Profit amount: %.2f\n", profit);
    } else {
        printf("None\n");
    }

    return EXIT_SUCCESS;
}