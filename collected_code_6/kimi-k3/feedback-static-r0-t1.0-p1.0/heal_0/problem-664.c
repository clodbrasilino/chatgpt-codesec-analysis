#include <stdio.h>

double findAverageOfEvenNumbers(int limit)
{
    if (limit < 2 || limit % 2 != 0)
    {
        return 0.0;
    }
    
    int count = limit / 2;
    long long sum = (long long)count * (count + 1);
    
    return (double)sum / count;
}

int main(void)
{
    int limit;
    
    printf("Enter an even number: ");
    
    if (scanf("%d", &limit) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }
    
    if (limit < 2 || limit % 2 != 0)
    {
        printf("Please enter a positive even number (>= 2).\n");
        return 1;
    }
    
    double average = findAverageOfEvenNumbers(limit);
    printf("Average of even numbers till %d: %.2f\n", limit, average);
    
    return 0;
}