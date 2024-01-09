#include<stdio.h>

// Function to find the greatest common divisor of two numbers
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to find the sum of common divisors of two numbers
int sumOfCommonDivisors(int a, int b) 
{ 
    int gcd_value = gcd(a, b); 
    int sum = 0; 
  
    // Finding divisors of gcd_value and adding them to sum
    for (int i = 1; i <= gcd_value; i++) 
    { 
        if (gcd_value % i == 0) 
            sum += i; 
    } 
  
    return sum; 
} 

int main()
{
    int num1, num2, result;
    
    printf("Enter the first number: ");
    scanf("%d", &num1);

    printf("Enter the second number: ");
    scanf("%d", &num2);

    result = sumOfCommonDivisors(num1, num2);
    printf("Sum of common divisors of %d and %d: %d\n", num1, num2, result);

    return 0;
}