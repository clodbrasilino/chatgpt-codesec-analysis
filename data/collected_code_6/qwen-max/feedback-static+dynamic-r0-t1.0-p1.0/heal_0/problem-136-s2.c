#include <stdio.h>

float calculateBill(float units) {
    float bill = 0;
    if (units <= 100) {
        bill = units * 2.5;
    } else if (units <= 300) {
        bill = 250 + (units - 100) * 4.0;
    } else {
        bill = 250 + 800 + (units - 300) * 6.0;
    }
    return bill;
}

int main() {
    float units;
    printf("Enter the number of units consumed: ");
    int res = scanf("%f", &units);
    if (res != 1) {
        fprintf(stderr, "Input error, please enter a valid number.");
        return 1;
    }
    float bill = calculateBill(units);
    printf("Total electricity bill: %.2f\n", bill);
    return 0;
}