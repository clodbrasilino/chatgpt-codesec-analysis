#include <stdio.h>

#define NONE (-1)

int calculateProfit(int amount, int cost) {
    if (amount > cost) {
        return amount - cost;
    }
    return NONE;
}

int main() {
    int amount, cost;
    printf("Enter the amount: ");
    scanf("%d", &amount);
    printf("Enter the cost: ");
    scanf("%d", &cost);

    int profit = calculateProfit(amount, cost);
    if (profit != NONE) {
        printf("Profit: %d\n", profit);
    } else {
        printf("No profit\n");
    }
    return 0;
}