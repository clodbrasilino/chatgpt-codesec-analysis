#include <stdio.h>
#include <stdlib.h>

#define NONE -1

int calculate_profit(int amount) {
    if (amount > 0) {
        return amount * 0.2; // Assuming a 20% profit
    }
    return NONE;
}

int main() {
    int amount = 1500;
    int profit = calculate_profit(amount);
    if (profit != NONE) {
        printf("Profit: %d\n", profit);
    } else {
        printf("No profit\n");
    }
    return 0;
}