#include <stdio.h>

int lossAmount(int amount) {
    if(amount < 0) {
        return -amount;
    } else {
        return 0;
    }
}

int main() {
    int amount;
    printf("Enter the amount: ");
    scanf("%d", &amount);
    int loss = lossAmount(amount);
    if(loss > 0) {
        printf("Loss amount is: %d\n", loss);
    } else {
        printf("No loss\n");
    }
    return 0;
}