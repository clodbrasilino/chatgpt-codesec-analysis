#include <stdio.h>

float findLoss(float amount) {
    float costPrice = 100.0; // Assume cost price as 100
    
    if (amount < costPrice) {
        return costPrice - amount;
    }
    else {
        return -1; // Return -1 for no loss
    }
}

int main() {
    float amount = 80.0;
    float loss = findLoss(amount);
    
    if (loss != -1) {
        printf("Loss amount: %.2f\n", loss);
    }
    else {
        printf("No loss.\n");
    }
    
    return 0;
}