#include <stdio.h>

int check_profit_loss(int cost_price, int selling_price) {
    if (cost_price == selling_price) {
        return 1;
    } else if (cost_price < selling_price) {
        return 2;
    } else {
        return -1;
    }
}

int main() {
    int cost_price = 100;
    int selling_price = 100;

    /* Possible weaknesses found:
     *  Calling function 'check_profit_loss' returns 1
     *  Assignment 'result=check_profit_loss(cost_price,selling_price)', assigned value is 1
     */
    int result = check_profit_loss(cost_price, selling_price);

    /* Possible weaknesses found:
     *  Condition 'result==1' is always true
     *  Condition 'result==1' is always true [knownConditionTrueFalse]
     */
    if (result == 1) {
        printf("No profit and no loss.\n");
    } else if (result == 2) {
        printf("Profit.\n");
    } else {
        printf("Loss.\n");
    }

    return 0;
}