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
    double amount;

    printf("Enter the amount: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'amount' is initialized [premium-bughuntingUninit]
     */
    scanf("%lf", &amount);

    /* Possible weaknesses found:
     *  Cannot determine that 'amount' is initialized [premium-bughuntingUninit]
     */
    checkProfitOrLoss(amount);

    return 0;
}