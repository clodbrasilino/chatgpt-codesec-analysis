#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <float.h>
#include <string.h>

int check_no_profit_no_loss(double cost_price, double selling_price) {
    if (cost_price < 0 || selling_price < 0) {
        return -1;
    }
    if (cost_price == selling_price) {
        return 1;
    }
    return 0;
}

int main(void) {
    double cost_price, selling_price;
    char input[256];
    char *endptr;

    printf("Enter cost price: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    cost_price = strtod(input, &endptr);
    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (errno == ERANGE || cost_price == HUGE_VAL || cost_price == -HUGE_VAL) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }

    printf("Enter selling price: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    selling_price = strtod(input, &endptr);
    if (endptr == input || *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (errno == ERANGE || selling_price == HUGE_VAL || selling_price == -HUGE_VAL) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }

    int result = check_no_profit_no_loss(cost_price, selling_price);
    if (result == -1) {
        fprintf(stderr, "Prices cannot be negative\n");
        return EXIT_FAILURE;
    }
    if (result == 1) {
        printf("No profit and no loss\n");
    } else {
        printf("There is profit or loss\n");
    }

    return EXIT_SUCCESS;
}