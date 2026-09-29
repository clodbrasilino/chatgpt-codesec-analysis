#include <stdio.h>

int checkNoProfitNoLoss(double costPrice, double sellingPrice) {
    if (costPrice == sellingPrice) {
        return 1;
    }
    return 0;
}

int main(void) {
    double costPrice = 0.0;
    double sellingPrice = 0.0;
    int result = 0;

    printf("Enter cost price: ");
    if (scanf("%lf", &costPrice) != 1) {
        printf("Invalid input for cost price.\n");
        return 1;
    }

    printf("Enter selling price: ");
    if (scanf("%lf", &sellingPrice) != 1) {
        printf("Invalid input for selling price.\n");
        return 1;
    }

    result = checkNoProfitNoLoss(costPrice, sellingPrice);

    if (result == 1) {
        printf("No profit, no loss.\n");
    } else {
        printf("There is either profit or loss.\n");
    }

    return 0;
}