#include <stdio.h>
#include <stdlib.h>

char *check_profit(double amount) {
    if (amount > 0.0) {
        return "Profit";
    }
    return "None";
}

int main() {
    double amount;
    printf("Enter the amount: ");
    if (scanf("%lf", &amount) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    char *result = check_profit(amount);
    printf("%s\n", result);

    return EXIT_SUCCESS;
}