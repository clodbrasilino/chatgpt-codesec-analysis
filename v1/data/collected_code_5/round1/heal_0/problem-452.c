#include <stdio.h>

float calculateLoss(float cost, float sale) {
    float loss = 0.0;

    if(cost > sale) {
        loss = cost - sale;
    }

    return loss;
}

int main() {
    float cost, sale, loss;

    printf("Enter the cost and sale prices: ");
    scanf("%f %f", &cost, &sale);

    loss = calculateLoss(cost, sale);

    if(loss > 0)
        printf("Loss amount: %.2f\n", loss);
    else
        printf("No loss.\n");

    return 0;
}