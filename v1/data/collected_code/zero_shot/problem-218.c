#include <stdio.h>

int minOperations(int num1, int num2) {
    int count = 0;
    
    while (num1 != num2) {
        if (num1 > num2) {
            num1 -= num2;
        } else {
            num2 -= num1;
        }
        count++;
    }
    
    return count;
}

int main() {
    int num1, num2;
    
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);
    
    int result = minOperations(num1, num2);
    
    printf("Minimum operations required: %d\n", result);
    
    return 0;
}