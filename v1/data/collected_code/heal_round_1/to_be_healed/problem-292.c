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
    /* Possible weaknesses found:
     *  Cannot determine that 'number1' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &number1);
    
    printf("Enter the second number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'number2' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &number2);
    
    result = findQuotient(number1, number2);
    
    printf("Quotient: %.2f\n", result);
    
    return 0;
}