#include <stdio.h>

int addAndPrintNumberOfDigits(int a, int b) {
    int sum = a + b;
    int digits = 0;
    
    if (sum == 0) {
        digits = 1;
    } else {
        while (sum != 0) {
            digits++;
            sum /= 10;
        }
    }
    
    printf("Number of digits in sum: %d\n", digits);
    
    return digits;
}

int main() {
    int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);
    
    addAndPrintNumberOfDigits(num1, num2);
    
    return 0;
}