#include <stdio.h>
#include <stdlib.h>

double calculate_bill(double units) {
    double bill_amount = 0.0;

    if (units < 0) {
        return -1.0;
    }

    if (units <= 50) {
        bill_amount = units * 0.50;
    } else if (units <= 150) {
        bill_amount = 25.0 + ((units - 50) * 0.75);
    } else if (units <= 250) {
        bill_amount = 100.0 + ((units - 150) * 1.20);
    } else {
        bill_amount = 220.0 + ((units - 250) * 1.50);
    }

    bill_amount = bill_amount + (bill_amount * 0.20);

    return bill_amount;
}

int main() {
    double units = 0.0;
    double bill_amount = 0.0;
    int items_read = 0;

    printf("Enter the number of units consumed: ");
    items_read = scanf("%lf", &units);

    if (items_read != 1) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    bill_amount = calculate_bill(units);

    if (bill_amount < 0.0) {
        printf("Invalid units entered.\n");
        return EXIT_FAILURE;
    }

    printf("Total Electricity Bill: Rs. %.2lf\n", bill_amount);

    return EXIT_SUCCESS;
}