#include <stdio.h>

int oppositeSigns(int x, int y)
{
    return ((x ^ y) < 0);
}

int main()
{
    int num1, num2;
    printf("Enter the first integer: ");
    scanf("%d", &num1);
    printf("Enter the second integer: ");
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