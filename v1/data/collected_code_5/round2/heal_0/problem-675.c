#include <stdio.h>

int addIntegersInRange(int num1, int num2, int minRange, int maxRange) {
    int sum = num1 + num2;
    
    if (sum >= minRange && sum <= maxRange) {
        return 20;
    }
    
    return sum;
}

int main() {
    int num1, num2, minRange, maxRange;
    printf("Enter two numbers to add: ");
    scanf("%d%d", &num1, &num2);
    
    printf("Enter a range: ");
    scanf("%d%d", &minRange, &maxRange);
    
    printf("Output: %d\n", addIntegersInRange(num1, num2, minRange, maxRange));
    
    return 0;
}