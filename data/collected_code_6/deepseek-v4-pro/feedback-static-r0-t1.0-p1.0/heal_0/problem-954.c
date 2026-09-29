#include <stdio.h>
#include <stdlib.h>

double calculate_profit(double amount, double cost) {
    return amount - cost;
}

int get_profit_or_none(double amount, double cost, double *profit) {
    if (profit == NULL) {
        return 0;
    }
    if (amount < cost) {
        return 0;
    }
    *profit = calculate_profit(amount, cost);
    return 1;
}

int main(void) {
    double amount = 150.0;
    double cost = 100.0;
    double profit = 0.0;

    if (get_profit_or_none(amount, cost, &profit)) {
        printf("Profit: %.2f\n", profit);
    } else {
        printf("No profit\n");
    }

    if (get_profit_or_none(50.0, 100.0, &profit)) {
        printf("Profit: %.2f\n", profit);
    } else {
        printf("No profit\n");
    }

    return 0;
}