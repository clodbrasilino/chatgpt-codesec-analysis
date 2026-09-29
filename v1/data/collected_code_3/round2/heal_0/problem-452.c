#include <stdio.h>

int lossAmount(int costPrice, int sellingPrice) {
    int loss = costPrice - sellingPrice;
    if(loss > 0) {
        return loss;
    }
    return 0;
}

int main() {
    int costPrice, sellingPrice;
    printf("Enter cost price: ");
    scanf("%d", &costPrice);
    printf("Enter selling price: ");
    scanf("%d", &sellingPrice);
    int loss = lossAmount(costPrice, sellingPrice);
    if(loss > 0) {
        printf("Loss amount is: %d\n", loss);
    } else {
        printf("No loss\n");
    }
    return 0;
}