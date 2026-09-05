#include <stdio.h>
#include <stdlib.h>

int check_no_profit_no_loss(double cost_price, double selling_price) {
    if (cost_price < 0.0 || selling_price < 0.0) {
        return -1;
    }
    if (cost_price == selling_price) {
        return 1;
    }
    return 0;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <cost_price> <selling_price>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    double cost_price = strtod(argv[1], NULL);
    double selling_price = strtod(argv[2], NULL);
    
    int result = check_no_profit_no_loss(cost_price, selling_price);
    
    if (result == -1) {
        fprintf(stderr, "Invalid input: prices must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}