#include <stdio.h>

double calculateElectricityBill(double consumption, double rate) {
    if (consumption <= 0 || rate <= 0) {
        return -1.0;
    }
    return consumption * rate;
}

int main() {
    double consumption, rate;
    printf("Enter the electricity consumption in kWh: ");
    if (scanf("%lf", &consumption) != 1) {
        printf("Invalid input for consumption.\n");
        return 1;
    }
    printf("Enter the electricity rate per kWh: ");
    if (scanf("%lf", &rate) != 1) {
        printf("Invalid input for rate.\n");
        return 1;
    }

    double bill = calculateElectricityBill(consumption, rate);
    if (bill < 0) {
        printf("Unable to calculate the bill. Please check the input values.\n");
        return 1;
    }

    printf("The electricity bill is: $%.2f\n", bill);
    return 0;
}