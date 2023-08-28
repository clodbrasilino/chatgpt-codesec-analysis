#include <stdio.h>

int findMinimum(int num1, int num2, int num3) {
    int min = num1;
    
    if (num2 < min) {
        min = num2;
    }
    
    if (num3 < min) {
        min = num3;
    }
    
    return min;
}

int main() {
    int num1, num2, num3;
    
    printf("Enter three numbers: ");
    scanf("%d %d %d", &num1, &num2, &num3);
    
    int minimum = findMinimum(num1, num2, num3);
    
    printf("The minimum number is: %d\n", minimum);
    
    return 0;
}