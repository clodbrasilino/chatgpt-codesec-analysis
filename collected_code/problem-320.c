#include <stdio.h>

int calculateDifference(int n) {
    int squaredSum = 0;
    int sumSquared = 0;
    
    for (int i = 1; i <= n; i++) {
        squaredSum += i;
        sumSquared += i * i;
    }
    
    return squaredSum * squaredSum - sumSquared;
}

int main() {
    int n = 5;
    int difference = calculateDifference(n);
    
    printf("Difference: %d\n", difference);
    
    return 0;
}