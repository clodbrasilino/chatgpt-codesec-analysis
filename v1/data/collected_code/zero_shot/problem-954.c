#include <stdio.h>

float calculateProfit(float amount) {
    if (amount > 0) {
        float costPrice = 100;
        float sellingPrice = amount;
        float profit = sellingPrice - costPrice;
        return profit;
    } else {
        return 0;
    }
}

int main() {
    float givenAmount = 150;
    float profitAmount = calculateProfit(givenAmount);

    if (profitAmount != 0) {
        printf("Profit amount: %.2f\n", profitAmount);
    } else {
        printf("None\n");
    }

    return 0;
}