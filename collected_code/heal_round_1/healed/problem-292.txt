#include <stdio.h>

float findQuotient(int num1, int num2){
    float quotient = (float)num1 / num2;
    return quotient;
}

int main()
{
    int number1 = 0, number2 = 0;
    float result;

    printf("Enter the first number: ");
    scanf("%d", &number1);
    
    printf("Enter the second number: ");
    scanf("%d", &number2);

    if (number2 == 0) {
        printf("Error: Division by zero is not allowed.\n");
        return -1;
    }
    
    result = findQuotient(number1, number2);
    
    printf("Quotient: %.2f\n", result);
    
    return 0;
}