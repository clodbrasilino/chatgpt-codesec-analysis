#include <stdio.h>

double calculateProfit(double costPrice, double sellingPrice) {
    double profit = sellingPrice - costPrice;
    if (profit > 0) {
        return profit;
    } else {
        return -1;
    }
}

int main() {
    double costPrice, sellingPrice, profit;

    printf("Enter cost price: ");
    scanf("%lf", &costPrice);

    printf("Enter selling price: ");
    scanf("%lf", &sellingPrice);

    profit = calculateProfit(costPrice, sellingPrice);

    if (profit != -1) {
        printf("Profit amount: %.2lf\n", profit);
    } else {
        printf("No profit\n");
    }

    return 0;
}