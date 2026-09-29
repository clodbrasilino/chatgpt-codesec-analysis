#include <stdio.h>
#include <stdlib.h>

int digit_distance(int num1, int num2) {
    int distance = 0;
    
    while (num1 > 0 && num2 > 0) {
        int digit1 = num1 % 10;
        int digit2 = num2 % 10;
        
        distance += abs(digit1 - digit2);
        
        num1 /= 10;
        num2 /= 10;
    }
    
    return distance;
}

int main() {
    int num1, num2;
    
    printf("Enter first integer: ");
    scanf("%d", &num1);

    printf("Enter second integer: ");
    scanf("%d", &num2);
    
    int distance = digit_distance(num1, num2);
    printf("Digit distance between %d and %d is %d\n", num1, num2, distance);
    
    return 0;
}