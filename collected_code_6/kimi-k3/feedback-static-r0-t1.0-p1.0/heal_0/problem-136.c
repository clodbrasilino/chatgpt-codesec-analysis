#include <stdio.h>

float calculateBill(int units) {
    float amount = 0.0f;
    
    if (units <= 50) {
        amount = units * 0.50f;
    } else if (units <= 150) {
        amount = 25.0f + ((units - 50) * 0.75f);
    } else if (units <= 250) {
        amount = 100.0f + ((units - 150) * 1.20f);
    } else {
        amount = 220.0f + ((units - 250) * 1.50f);
    }
    
    return amount * 1.20f;
}

int main(void) {
    int units;
    
    printf("Enter units consumed: ");
    
    if (scanf("%d", &units) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (units < 0) {
        fprintf(stderr, "Units cannot be negative\n");
        return 1;
    }
    
    printf("Electricity Bill: Rs. %.2f\n", calculateBill(units));
    
    return 0;
}