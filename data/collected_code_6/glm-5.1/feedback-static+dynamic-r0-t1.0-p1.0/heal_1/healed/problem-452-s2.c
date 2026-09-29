#include <stdio.h>
#include <stdlib.h>

int calculate_loss(int cost_price, int selling_price) {
    if (cost_price < 0 || selling_price < 0) {
        return -1;
    }

    if (cost_price > selling_price) {
        return cost_price - selling_price;
    }

    return -1;
}

int main() {
    int cp = 100;
    int sp = 80;

    int loss = calculate_loss(cp, sp);

    if (loss != -1) {
        printf("%d\n", loss);
    } else {
        printf("none\n");
    }

    int cp2 = 50;
    int sp2 = 60;

    int loss2 = calculate_loss(cp2, sp2);

    if (loss2 != -1) {
        printf("%d\n", loss2);
    } else {
        printf("none\n");
    }

    return 0;
}