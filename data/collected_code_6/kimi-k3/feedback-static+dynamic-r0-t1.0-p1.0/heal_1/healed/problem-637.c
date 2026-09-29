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

    if (scanf("%lf", &costPrice) != 1) {
        return 1;
    }

    if (scanf("%lf", &sellingPrice) != 1) {
        return 1;
    }

    result = checkNoProfitNoLoss(costPrice, sellingPrice);

    if (result == 1) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}