#include <stdio.h>
#include <stdlib.h>

double calculate_electricity_bill(int units) {
    double bill = 0.0;
    if (units < 0) {
        return -1.0;
    }
    if (units <= 100) {
        bill = units * 1.5;
    } else if (units <= 200) {
        bill = 100 * 1.5 + (units - 100) * 2.5;
    } else if (units <= 300) {
        bill = 100 * 1.5 + 100 * 2.5 + (units - 200) * 4.0;
    } else {
        bill = 100 * 1.5 + 100 * 2.5 + 100 * 4.0 + (units - 300) * 6.0;
    }
    return bill;
}

int main(void) {
    int units = 0;
    printf("Enter electricity units consumed: ");
    if (scanf("%d", &units) != 1) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }
    double total_bill = calculate_electricity_bill(units);
    if (total_bill < 0.0) {
        printf("Invalid units consumed.\n");
        return EXIT_FAILURE;
    }
    printf("Total electricity bill: %.2lf\n", total_bill);
    return EXIT_SUCCESS;
}