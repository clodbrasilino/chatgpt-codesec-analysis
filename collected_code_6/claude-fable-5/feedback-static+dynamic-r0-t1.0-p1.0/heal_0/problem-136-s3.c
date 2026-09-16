#include <stdio.h>
#include <stdlib.h>

double calculate_bill(double units);

double calculate_bill(double units)
{
    double bill = 0.0;

    if (units <= 0.0) {
        return 0.0;
    }

    if (units <= 100.0) {
        bill = units * 1.50;
    } else if (units <= 200.0) {
        bill = (100.0 * 1.50) + ((units - 100.0) * 2.50);
    } else if (units <= 300.0) {
        bill = (100.0 * 1.50) + (100.0 * 2.50) + ((units - 200.0) * 4.00);
    } else {
        bill = (100.0 * 1.50) + (100.0 * 2.50) + (100.0 * 4.00) + ((units - 300.0) * 6.00);
    }

    bill += bill * 0.05;

    return bill;
}

int main(void)
{
    double units = 0.0;
    double bill = 0.0;
    int result = 0;

    printf("Enter units consumed: ");

    result = scanf("%lf", &units);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (units < 0.0) {
        fprintf(stderr, "Error: units cannot be negative.\n");
        return EXIT_FAILURE;
    }

    if (units > 1000000.0) {
        fprintf(stderr, "Error: units value too large.\n");
        return EXIT_FAILURE;
    }

    bill = calculate_bill(units);

    printf("Units consumed: %.2f\n", units);
    printf("Total bill: %.2f\n", bill);

    return EXIT_SUCCESS;
}