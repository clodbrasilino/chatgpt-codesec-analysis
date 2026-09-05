#include <stdio.h>
#include <stdbool.h>

bool calculate_profit(double amount, double *profit) {
    if (profit == NULL) {
        return false;
    }
    if (amount > 0.0) {
        *profit = amount * 0.10;
        return true;
    }
    return false;
}

int main(void) {
    double amount = 150.0;
    double profit = 0.0;
    
    if (calculate_profit(amount, &profit)) {
        printf("Profit: %.2f\n", profit);
    } else {
        printf("No profit\n");
    }
    
    return 0;
}