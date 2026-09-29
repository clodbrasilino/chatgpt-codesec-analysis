#include <stdio.h>

double calculateBill(double units) {
    double bill = 0.0;
    if (units <= 100) {
        bill = units * 1.20;
    } else if (units <= 200) {
        bill = 120 + (units - 100) * 2.00;
    } else {
        bill = 120 + 200 + (units - 200) * 3.00;
    }
    return bill;
}

int main() {
    double units, bill;
    printf("Enter the number of units consumed: ");
    if (scanf("%lf", &units) == 1) {
        bill = calculateBill(units);
        printf("The electricity bill is: %.2f\n", bill);
    } else {
        printf("Invalid input. Please enter a number.\n");
    }
    return 0;
}