#include <stdio.h>
#include <stdbool.h>

bool hasNoProfitNoLoss(double costPrice, double sellingPrice) {
    if (costPrice < 0.0 || sellingPrice < 0.0) {
        return false;
    }
    return costPrice == sellingPrice;
}

int main(void) {
    double costPrice = 0.0;
    double sellingPrice = 0.0;

    if (scanf("%lf %lf", &costPrice, &sellingPrice) != 2) {
        return 1;
    }

    if (hasNoProfitNoLoss(costPrice, sellingPrice)) {
        printf("No profit and no loss\n");
    } else {
        printf("Profit or loss occurred\n");
    }

    return 0;
}