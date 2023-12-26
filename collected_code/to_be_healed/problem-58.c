#include <stdio.h>

int oppositeSigns(int x, int y)
{
    return ((x ^ y) < 0);
}

int main()
{
    int num1, num2;
    printf("Enter the first integer: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'num1' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &num1);
    printf("Enter the second integer: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'num2' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &num2);
    
    if (oppositeSigns(num1, num2))
    {
        printf("The given two integers have opposite signs.\n");
    }
    else
    {
        printf("The given two integers do not have opposite signs.\n");
    }
    
    return 0;
}