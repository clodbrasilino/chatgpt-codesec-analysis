#include <stdio.h>

int check_profit_loss(int cost_price, int selling_price) {
    if (cost_price == selling_price) {
        return 1;
    }
    return 0;
}

int main() {
    int cost_price = 100;
    int selling_price = 100;

    /* Possible weaknesses found:
     *  Condition 'check_profit_loss(cost_price,selling_price)' is always true [knownConditionTrueFalse]
     *  Calling function 'check_profit_loss' returns 1
     *  Condition 'check_profit_loss(cost_price,selling_price)' is always true
     */
    if (check_profit_loss(cost_price, selling_price)) {
        printf("No profit and no loss.\n");
    } else {
        printf("There is either a profit or a loss.\n");
    }

    return 0;
}