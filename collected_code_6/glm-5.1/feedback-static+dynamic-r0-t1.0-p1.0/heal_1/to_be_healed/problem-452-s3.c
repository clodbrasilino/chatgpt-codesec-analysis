#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int has_loss;
    double loss_amount;
} LossResult;

LossResult calculate_loss(double cost_price, double selling_price) {
    LossResult result;
    if (cost_price > selling_price) {
        result.has_loss = 1;
        result.loss_amount = cost_price - selling_price;
    } else {
        result.has_loss = 0;
        result.loss_amount = 0.0;
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <cost_price> <selling_price>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    double cost = strtod(argv[1], &endptr);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid cost price\n");
        return EXIT_FAILURE;
    }

    double sell = strtod(argv[2], &endptr);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid selling price\n");
        return EXIT_FAILURE;
    }

    LossResult res = calculate_loss(cost, sell);
    if (res.has_loss) {
        printf("Loss: %.2f\n", res.loss_amount);
    } else {
        printf("None\n");
    }

    return EXIT_SUCCESS;
}