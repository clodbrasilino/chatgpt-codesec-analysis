#include <stdio.h>

int calculateLoss(int costPrice, int sellingPrice) {
    if (costPrice > sellingPrice) {
        return costPrice - sellingPrice;
    } else {
        return 0;
    }
}

int main() {
    int costPrice, sellingPrice, loss;

    printf("Enter cost price: ");
    scanf("%d", &costPrice);

    printf("Enter selling price: ");
    scanf("%d", &sellingPrice);

    loss = calculateLoss(costPrice, sellingPrice);

    if (loss > 0) {
        printf("Loss amount is: %d\n", loss);
    } else {
        printf("No loss\n");
    }

    return 0;
}