#include <stdio.h>
#include <stdlib.h>

int calculate_loss(int cost_price, int selling_price) {
    if (cost_price < 0 || selling_price < 0) {
        return -1;
    }

    if (cost_price > selling_price) {
        return cost_price - selling_price;
    }

    return 0;
}

int main() {
    int cp, sp;
    
    if (scanf("%d %d", &cp, &sp) == 2) {
        int loss = calculate_loss(cp, sp);
        if (loss > 0) {
            printf("%d\n", loss);
        } else {
            printf("none\n");
        }
    }

    return 0;
}