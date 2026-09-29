#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_break_even(long long cost_price, long long selling_price);

bool is_break_even(long long cost_price, long long selling_price)
{
    return cost_price == selling_price;
}

int main(void)
{
    long long cost_price;
    long long selling_price;

    printf("Enter cost price: ");
    if (scanf("%lld", &cost_price) != 1) {
        fprintf(stderr, "Invalid input for cost price.\n");
        return EXIT_FAILURE;
    }

    printf("Enter selling price: ");
    if (scanf("%lld", &selling_price) != 1) {
        fprintf(stderr, "Invalid input for selling price.\n");
        return EXIT_FAILURE;
    }

    if (cost_price < 0 || selling_price < 0) {
        fprintf(stderr, "Prices must be non-negative.\n");
        return EXIT_FAILURE;
    }

    if (is_break_even(cost_price, selling_price)) {
        printf("No profit and no loss.\n");
    } else if (selling_price > cost_price) {
        printf("There is a profit of %lld.\n", selling_price - cost_price);
    } else {
        printf("There is a loss of %lld.\n", cost_price - selling_price);
    }

    return EXIT_SUCCESS;
}