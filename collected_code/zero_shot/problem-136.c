#include <stdio.h>

float calculateElectricityBill(float units) {
    float rate, totalBill;
  
    if(units <= 50) {
        rate = 0.50;
    } else if(units <= 150) {
        rate = 0.75;
    } else if(units <= 250) {
        rate = 1.20;
    } else {
        rate = 1.50;
    }
    
    totalBill = units * rate;
    return totalBill;
}

int main() {
    float units;
    
    printf("Enter the number of units consumed: ");
    scanf("%f", &units);
    
    if(units < 0) {
        printf("Invalid input! Number of units cannot be negative.");
        return 0;
    }
    
    float bill = calculateElectricityBill(units);
    printf("Electricity bill for %.2f units: $%.2f\n", units, bill);
    
    return 0;
}