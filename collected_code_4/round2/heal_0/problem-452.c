#include <stdio.h>

float calculateLoss(float costPrice, float sellingPrice) {
    if(costPrice < 0 || sellingPrice < 0) {
        printf("Invalid input");
        return -1;
    }
    if(costPrice > sellingPrice) {
        return costPrice - sellingPrice;
    }
    return 0;
}

int main() {
    float cost, sell;

    printf("Enter cost price: ");
    scanf("%f", &cost);
    printf("Enter selling price: ");
    scanf("%f", &sell);

    float loss = calculateLoss(cost, sell);

    if(loss == -1) {
        printf("Invalid input\n");
    } else if(loss == 0) {
        printf("No Loss\n");
    } else {
        printf("Loss = %.2f\n", loss);
    }

    return 0;
}