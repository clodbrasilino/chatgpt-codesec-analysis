#include <stdio.h>
#include <stdlib.h>

int calculate_loss(int cost_price, int selling_price, int *loss) {
    if (cost_price < 0 || selling_price < 0) {
        *loss = 0;
        return -1;
    }

    if (cost_price > selling_price) {
        *loss = cost_price - selling_price;
        return 0;
    }

    *loss = 0;
    return 1;
}

int main() {
    int cp, sp, loss;
    int cp2, sp2, loss2;

    printf("Enter cost price and selling price: ");
    if (scanf("%d %d", &cp, &sp) != 2) {
        return 1;
    }

    printf("Enter cost price and selling price: ");
    if (scanf("%d %d", &cp2, &sp2) != 2) {
        return 1;
    }

    loss = 0;
    loss2 = 0;

    if (calculate_loss(cp, sp, &loss) == 0) {
        printf("%d\n", loss);
    } else {
        printf("none\n");
    }

    if (calculate_loss(cp2, sp2, &loss2) == 0) {
        printf("%d\n", loss2);
    } else {
        printf("none\n");
    }

    return 0;
}