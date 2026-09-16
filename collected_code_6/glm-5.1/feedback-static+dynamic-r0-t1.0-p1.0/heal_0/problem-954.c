#include <stdio.h>
#include <stdlib.h>

int* get_profit_amount(int cost_price, int selling_price) {
    int profit = selling_price - cost_price;
    if (profit > 0) {
        int* profit_ptr = (int*)malloc(sizeof(int));
        if (profit_ptr == NULL) {
            return NULL;
        }
        *profit_ptr = profit;
        return profit_ptr;
    }
    return NULL;
}

int main() {
    int cost_price = 50;
    int selling_price = 75;

    int* profit_result = get_profit_amount(cost_price, selling_price);

    if (profit_result != NULL) {
        printf("%d\n", *profit_result);
        free(profit_result);
    } else {
        printf("None\n");
    }

    profit_result = get_profit_amount(75, 50);

    if (profit_result != NULL) {
        printf("%d\n", *profit_result);
        free(profit_result);
    } else {
        printf("None\n");
    }

    return 0;
}