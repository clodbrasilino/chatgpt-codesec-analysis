#include <stdio.h>
#include <stdlib.h>

int check_no_profit_no_loss(double cost_price, double selling_price) {
    if (cost_price < 0 || selling_price < 0) {
        return -1;
    }
    if (selling_price == cost_price) {
        return 1;
    }
    return 0;
}

int main() {
    double cp = 100.0;
    double sp = 100.0;
    int result = check_no_profit_no_loss(cp, sp);
    if (result == 1) {
        printf("No profit no loss\n");
    } else if (result == 0) {
        printf("Either profit or loss\n");
    } else {
        printf("Invalid input\n");
    }
    return 0;
}