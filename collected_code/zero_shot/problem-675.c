#include <stdio.h>

int addIntegers(int a, int b) {
    int sum = a + b;

    if(sum >= 10 && sum <= 20) {
        return 20;
    }

    return sum;
}

int main() {
    int num1, num2;

    printf("Enter first integer: ");
    scanf("%d", &num1);
    
    printf("Enter second integer: ");
    scanf("%d", &num2);

    int result = addIntegers(num1, num2);

    printf("Result: %d\n", result);

    return 0;
}