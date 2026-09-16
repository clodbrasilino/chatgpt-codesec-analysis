#include <stdio.h>
#include <stdlib.h>

double calculateElectricityBill(double units) {
    double totalBill = 0.0;

    if (units < 0.0) {
        return -1.0;
    }

    if (units <= 50.0) {
        totalBill = units * 0.50;
    } else if (units <= 150.0) {
        totalBill = (50.0 * 0.50) + ((units - 50.0) * 0.75);
    } else if (units <= 250.0) {
        totalBill = (50.0 * 0.50) + (100.0 * 0.75) + ((units - 150.0) * 1.20);
    } else {
        totalBill = (50.0 * 0.50) + (100.0 * 0.75) + (100.0 * 1.20) + ((units - 250.0) * 1.50);
    }

    totalBill += totalBill * 0.20;

    return totalBill;
}

int main() {
    double units;
    double bill;
    int result;

    printf("Enter total units consumed: ");
    result = scanf("%lf", &units);

    if (result != 1) {
        printf("Invalid input. Please enter a numerical value.\n");
        return EXIT_FAILURE;
    }

    bill = calculateElectricityBill(units);

    if (bill < 0.0) {
        printf("Invalid units. Units cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("Electricity Bill: $%.2f\n", bill);

    return EXIT_SUCCESS;
}