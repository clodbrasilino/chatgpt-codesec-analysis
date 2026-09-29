#include<stdio.h>

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int sumOfCommonDivisors(int a, int b) 
{ 
    int gcd_value = gcd(a, b); 
    int sum = 0; 
    for (int i = 1; i <= gcd_value; i++) 
    { 
        if (gcd_value % i == 0) 
            sum += i; 
    } 
    return sum; 
} 

int main()
{
    int num1 = 0, num2 = 0, result = 0;
   
    printf("Enter the first number: ");
    scanf("%d", &num1);

    printf("Enter the second number: ");
    scanf("%d", &num2);

    result = sumOfCommonDivisors(num1, num2);
    printf("Sum of common divisors of %d and %d: %d\n", num1, num2, result);

    return 0;
}