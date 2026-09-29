#include <stdio.h>

// Function to calculate sum of fourth power of first n odd natural numbers
long long int sumOfOddPower(int n)
{
    long long int sum = 0;
    for(int i = 1; i <= 2*n-1; i += 2) {
        sum += (long long int)i * i * i * i;
    }
   return sum;
}

//Main function
int main() 
{
    int n;
    printf("Enter a positive integer: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Input must be a positive integer.\n");
        return 1;
    }

    long long int sum = sumOfOddPower(n);
    printf("Sum of the squares of first %d odd natural numbers is: %lld\n", n, sum);

    return 0;
}