#include <stdio.h>
#include <stdlib.h>

int check_no_profit_no_loss(double cost_price, double selling_price) {
    if (cost_price < 0.0 || selling_price < 0.0) {
        return -1;
    }
    if (selling_price == cost_price) {
        return 1;
    }
    return 0;
}

int main(int argc, char const * const * argv) {
    double cost_price, selling_price;
    int result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <cost_price> <selling_price>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%lf", &cost_price) != 1) {
        return EXIT_FAILURE;
    }

    if (sscanf(argv[2], "%lf", &selling_price) != 1) {
        return EXIT_FAILURE;
    }

    result = check_no_profit_no_loss(cost_price, selling_price);

    if (result == 1) {
        printf("No profit no loss\n");
    } else if (result == 0) {
        printf("Either profit or loss\n");
    } else {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}