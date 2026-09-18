#include <stdio.h>
#include <stdlib.h>

int find_digit_distance(int num1, int num2) 
{
    int digitDistance = 0;

    while(num1 > 0 || num2 > 0)
    {
        int digit1 = num1 % 10;
        int digit2 = num2 % 10;

        digitDistance += abs(digit1 - digit2);

        num1 /= 10;
        num2 /= 10;
    }

    return digitDistance;
}

int main()
{
    int num1, num2;

    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    int digitDistance = find_digit_distance(num1, num2);
    printf("The digit distance between the two numbers is: %d\n", digitDistance);

    return 0;
}