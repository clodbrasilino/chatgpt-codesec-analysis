#include <stdio.h>

int check_no_profit_no_loss(double cost_price, double selling_price) {
    if (cost_price == selling_price) {
        return 1;
    }
    return 0;
}

int main(void) {
    double cost_price, selling_price;
    
    printf("Enter cost price: ");
    if (scanf("%lf", &cost_price) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("Enter selling price: ");
    if (scanf("%lf", &selling_price) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (check_no_profit_no_loss(cost_price, selling_price)) {
        printf("No profit and no loss\n");
    } else {
        printf("There is profit or loss\n");
    }
    
    return 0;
}