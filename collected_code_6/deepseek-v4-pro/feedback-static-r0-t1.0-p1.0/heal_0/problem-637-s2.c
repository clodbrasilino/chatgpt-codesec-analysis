#include <stdio.h>

int has_no_profit_no_loss(double cost_price, double selling_price) {
    return cost_price == selling_price;
}

int main(void) {
    double cost_price;
    double selling_price;
    
    printf("Enter cost price: ");
    scanf("%lf", &cost_price);
    
    printf("Enter selling price: ");
    scanf("%lf", &selling_price);
    
    if (has_no_profit_no_loss(cost_price, selling_price)) {
        printf("No profit and no loss\n");
    } else {
        printf("Profit or loss exists\n");
    }
    
    return 0;
}