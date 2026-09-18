#include <stdio.h>

int sumOfOddNumbers(int l, int r)
{
    int sum = 0;
    int i;

    for (i = l; i <= r; i++)
    {
        if (i % 2 != 0)
        {
            sum += i;
        }
    }

    return sum;
}

int main()
{
    int l, r;
    
    printf("Enter the starting range: ");
    scanf("%d", &l);
    
    printf("Enter the ending range: ");
    scanf("%d", &r);

    int result = sumOfOddNumbers(l, r);

    printf("Sum of odd numbers in the given range is %d\n", result);

    return 0;
}