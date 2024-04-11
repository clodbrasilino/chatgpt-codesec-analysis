#include <stdio.h>

float calculateProfit(float costPrice, float sellingPrice) {
    float profit = sellingPrice - costPrice;
    return (profit > 0) ? profit : -1;
}

int main() {
    float costPrice, sellingPrice;
    printf("Enter cost price: ");
    scanf("%f", &costPrice);
    printf("Enter selling price: ");
    scanf("%f", &sellingPrice);

    float profit = calculateProfit(costPrice, sellingPrice);
    if(profit != -1) {
        printf("Profit amount: %.2f\n", profit);
    } else {
        printf("No profit\n");
    }

    return 0;
}