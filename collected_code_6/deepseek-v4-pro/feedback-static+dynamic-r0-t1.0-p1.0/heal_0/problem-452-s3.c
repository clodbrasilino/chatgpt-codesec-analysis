#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int has_loss;
    double loss_amount;
} LossResult;

LossResult get_loss(double cost_price, double selling_price) {
    LossResult result;
    result.has_loss = 0;
    result.loss_amount = 0.0;
    
    if (selling_price < cost_price) {
        result.has_loss = 1;
        result.loss_amount = cost_price - selling_price;
    }
    
    return result;
}

int main(void) {
    double cost_price, selling_price;
    LossResult loss_result;
    
    printf("Enter cost price: ");
    if (scanf("%lf", &cost_price) != 1) {
        fprintf(stderr, "Invalid input for cost price\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter selling price: ");
    if (scanf("%lf", &selling_price) != 1) {
        fprintf(stderr, "Invalid input for selling price\n");
        return EXIT_FAILURE;
    }
    
    loss_result = get_loss(cost_price, selling_price);
    
    if (loss_result.has_loss) {
        printf("Loss amount: %.2f\n", loss_result.loss_amount);
    } else {
        printf("No loss\n");
    }
    
    return EXIT_SUCCESS;
}