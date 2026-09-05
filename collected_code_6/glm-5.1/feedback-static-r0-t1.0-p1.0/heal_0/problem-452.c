#include <stdio.h>
#include <stdlib.h>

int* calculate_loss(int cost_price, int selling_price) {
    if (selling_price < cost_price) {
        int* loss = malloc(sizeof(int));
        if (loss == NULL) {
            return NULL;
        }
        *loss = cost_price - selling_price;
        return loss;
    }
    return NULL;
}

int main() {
    int cp = 100;
    int sp = 80;
    int* loss_ptr = calculate_loss(cp, sp);
    if (loss_ptr != NULL) {
        printf("Loss amount: %d\n", *loss_ptr);
        free(loss_ptr);
    } else {
        printf("none\n");
    }
    return 0;
}