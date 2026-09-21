#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int check_no_profit_no_loss(double cost_price, double selling_price) {
    if (cost_price < 0.0 || selling_price < 0.0) {
        return -1;
    }
    if (cost_price == selling_price) {
        return 1;
    }
    return 0;
}

int main(int argc, char const * const * argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <cost_price> <selling_price>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr1;
    double cost_price = strtod(argv[1], &endptr1);
    if (errno != 0 || *endptr1 != '\0' || endptr1 == argv[1]) {
        fprintf(stderr, "Invalid input: cost_price must be a valid number\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr2;
    double selling_price = strtod(argv[2], &endptr2);
    if (errno != 0 || *endptr2 != '\0' || endptr2 == argv[2]) {
        fprintf(stderr, "Invalid input: selling_price must be a valid number\n");
        return EXIT_FAILURE;
    }

    int result = check_no_profit_no_loss(cost_price, selling_price);

    if (result == -1) {
        fprintf(stderr, "Invalid input: prices must be non-negative\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}