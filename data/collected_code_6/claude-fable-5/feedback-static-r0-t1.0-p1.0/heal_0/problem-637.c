#include <stdio.h>
#include <stdbool.h>

bool is_break_even(double cost_price, double selling_price)
{
    double diff = selling_price - cost_price;
    return (diff > -0.000001) && (diff < 0.000001);
}

int main(void)
{
    double cost_price = 0.0;
    double selling_price = 0.0;

    printf("Enter cost price: ");
    if (scanf("%lf", &cost_price) != 1)
    {
        fprintf(stderr, "Invalid input for cost price.\n");
        return 1;
    }

    printf("Enter selling price: ");
    if (scanf("%lf", &selling_price) != 1)
    {
        fprintf(stderr, "Invalid input for selling price.\n");
        return 1;
    }

    if (cost_price < 0.0 || selling_price < 0.0)
    {
        fprintf(stderr, "Prices must be non-negative.\n");
        return 1;
    }

    if (is_break_even(cost_price, selling_price))
    {
        printf("No profit and no loss.\n");
    }
    else if (selling_price > cost_price)
    {
        printf("Profit of %.2f\n", selling_price - cost_price);
    }
    else
    {
        printf("Loss of %.2f\n", cost_price - selling_price);
    }

    return 0;
}