#include <stdio.h>

float findQuotient(int num1, int num2){
    float quotient = (float)num1 / num2;
    return quotient;
}

int main()
{
    int number1, number2;
    float result;
    
    printf("Enter the first number: ");
    scanf("%d", &number1);
    
    printf("Enter the second number: ");
    scanf("%d", &number2);
    
    result = findQuotient(number1, number2);
    
    printf("Quotient: %.2f\n", result);
    
    return 0;
}