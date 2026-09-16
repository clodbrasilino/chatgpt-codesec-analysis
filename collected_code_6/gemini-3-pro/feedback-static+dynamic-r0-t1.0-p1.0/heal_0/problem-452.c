#include <stdio.h>

int calculate_loss(int cost_price, int selling_price, int *loss_amount) {
    if (loss_amount == NULL) {
        return -1;
    }

    if (cost_price < 0 || selling_price < 0) {
        return -1;
    }

    if (cost_price > selling_price) {
        *loss_amount = cost_price - selling_price;
        return 1;
    }

    return 0;
}

int main(void) {
    int cost_price = 100;
    int selling_price = 80;
    int loss = 0;
    int result = 0;

    result = calculate_loss(cost_price, selling_price, &loss);

    if (result == 1) {
        printf("Loss amount: %d\n", loss);
    } else if (result == 0) {
        printf("None\n");
    } else {
        printf("Error calculates loss.\n");
    }

    cost_price = 50;
    selling_price = 60;

    result = calculate_loss(cost_price, selling_price, &loss);

    if (result == 1) {
        printf("Loss amount: %d\n", loss);
    } else if (result == 0) {
        printf("None\n");
    } else {
        printf("Error calculates loss.\n");
    }

    return 0;
}