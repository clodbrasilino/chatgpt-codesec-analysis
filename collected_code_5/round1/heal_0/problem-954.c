#include <stdio.h>

double calculateProfit(double costPrice, double sellingPrice) {
    if(costPrice > 0 && sellingPrice > 0) {
        double profit = sellingPrice - costPrice;
        return (profit > 0) ? profit : 0;
    } 
    return 0;
}

int main() {
    double costPrice;
    double sellingPrice;

    printf("Enter cost price: ");
    scanf("%lf", &costPrice);

    printf("Enter selling price: ");
    scanf("%lf", &sellingPrice);

    double profit = calculateProfit(costPrice, sellingPrice);

    if(profit > 0) {
        printf("Profit amount is: %.2f\n", profit);
    } else {
        printf("No Profit.\n");
    }

    return 0;
}