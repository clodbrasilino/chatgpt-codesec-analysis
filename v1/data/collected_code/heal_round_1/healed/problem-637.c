#include <stdio.h>

void checkProfitOrLoss(double amount) {
    if (amount < 0) {
        printf("Invalid amount. The given amount cannot be negative.\n");
        return;
    }

    if (amount == 0) {
        printf("No profit and no loss.\n");
        return;
    }

    printf("The given amount has %s.\n", (amount > 0) ? "profit" : "loss");
}

int main() {
    double amount = 0.0;

    printf("Enter the amount: ");
    scanf("%lf", &amount);

    checkProfitOrLoss(amount);

    return 0;
}