#include <stdio.h>

int findCommonDivisor(int num1, int num2) {
    int smallestNum = (num1 < num2) ? num1 : num2;
    int commonDivisor = 1;
    
    for (int i = 2; i <= smallestNum; i++) {
        if (num1 % i == 0 && num2 % i == 0) {
            commonDivisor = i;
        }
    }
    
    return commonDivisor;
}

int main() {
    int num1 = 0, num2 = 0;
    
    printf("Enter the first number: ");
    scanf("%d", &num1);
    
    printf("Enter the second number: ");
    scanf("%d", &num2);
    
    int commonDivisor = findCommonDivisor(num1, num2);
    
    printf("The common divisor between %d and %d is %d", num1, num2, commonDivisor);
    
    return 0;
}