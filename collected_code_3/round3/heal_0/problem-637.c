#include <stdio.h>

int checkProfitLoss(int costPrice, int sellingPrice) {
    if(costPrice == sellingPrice) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int costPrice, sellingPrice;
    printf("Enter cost price: ");
    scanf("%d", &costPrice);
    printf("Enter selling price: ");
    scanf("%d", &sellingPrice);

    if(checkProfitLoss(costPrice, sellingPrice)) {
        printf("No Profit No Loss\n");
    } else {
        printf("There is either Profit or Loss\n");
    }

    return 0;
}