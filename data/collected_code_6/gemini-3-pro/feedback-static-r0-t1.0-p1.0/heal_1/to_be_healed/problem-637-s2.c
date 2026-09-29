#include <stdio.h>
#include <stdlib.h>

int check_no_profit_no_loss(int cost_price, int selling_price) {
    if (cost_price < 0 || selling_price < 0) {
        return -1;
    }
    if (cost_price == selling_price) {
        return 1;
    }
    return 0;
}

int main(void) {
    int cost_price = 100;
    int selling_price = 100;

    /* Possible weaknesses found:
     *  Assignment 'result=check_no_profit_no_loss(cost_price,selling_price)', assigned value is 1
     *  Calling function 'check_no_profit_no_loss' returns 1
     */
    int result = check_no_profit_no_loss(cost_price, selling_price);

    /* Possible weaknesses found:
     *  Condition 'result==1' is always true
     *  Condition 'result==1' is always true [knownConditionTrueFalse]
     */
    if (result == 1) {
        printf("No profit and no loss.\n");
    } else if (result == 0) {
        printf("Profit or loss occurred.\n");
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}