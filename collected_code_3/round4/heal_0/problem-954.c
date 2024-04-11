#include <stdio.h>

double calculateProfit(double costPrice, double sellingPrice) {
    double profit = sellingPrice - costPrice;
    return profit > 0 ? profit : -1;
}

int main() {
    double costPrice, sellingPrice;
    printf("Enter cost price: ");
    scanf("%lf", &costPrice);
    printf("Enter selling price: ");
    scanf("%lf", &sellingPrice);

    double profit = calculateProfit(costPrice, sellingPrice);
    if(profit != -1) {
        printf("Profit: %.2lf\n", profit);
    } else {
        printf("No Profit\n");
    }

    return 0;
}