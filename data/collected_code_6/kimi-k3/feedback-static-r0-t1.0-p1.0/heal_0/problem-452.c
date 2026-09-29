#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int calculate_loss(double cost_price, double selling_price, double *loss)
{
    if (loss == NULL) {
        return -1;
    }
    
    if (cost_price < 0 || selling_price < 0) {
        return -1;
    }
    
    if (selling_price < cost_price) {
        *loss = cost_price - selling_price;
        return 1;
    }
    
    return 0;
}

int main(void)
{
    double cost_price;
    double selling_price;
    double loss;
    int result;
    
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
    
    result = calculate_loss(cost_price, selling_price, &loss);
    
    if (result == -1) {
        fprintf(stderr, "Error: Invalid parameters\n");
        return EXIT_FAILURE;
    } else if (result == 1) {
        printf("Loss amount: %.2f\n", loss);
    } else {
        printf("No loss\n");
    }
    
    return EXIT_SUCCESS;
}