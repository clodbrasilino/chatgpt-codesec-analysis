#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_no_profit_no_loss(double cost_price, double selling_price) {
    return fabs(cost_price - selling_price) < 1e-9;
}

int main(void) {
    double cost_price, selling_price;

    if (scanf("%lf", &cost_price) != 1) {
        return 1;
    }

    if (scanf("%lf", &selling_price) != 1) {
        return 1;
    }

    if (is_no_profit_no_loss(cost_price, selling_price)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}