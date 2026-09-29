#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static int calculate_loss(double cost_price, double selling_price, double *loss)
{
    if (loss == NULL || cost_price < 0.0 || selling_price < 0.0) {
        return -1;
    }

    *loss = cost_price > selling_price ? cost_price - selling_price : 0.0;
    return 0;
}

int main(void)
{
    double cost_price;
    double selling_price;
    double loss;

    errno = 0;
    if (scanf("%lf %lf", &cost_price, &selling_price) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_loss(cost_price, selling_price, &loss) != 0) {
        fputs("Invalid amount\n", stderr);
        return EXIT_FAILURE;
    }

    if (loss > 0.0) {
        printf("%.2f\n", loss);
    } else {
        puts("none");
    }

    return EXIT_SUCCESS;
}