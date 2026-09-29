#include <stdio.h>

#define MAX 1000

int bell[MAX][MAX];

int getBellNumber(int n)
{
    bell[0][0] = 1;

    for (int i = 1; i <= n; i++)
    {
        bell[i][0] = bell[i - 1][i - 1];

        for (int j = 1; j <= i; j++)
        {
            bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1];
        }
    }

    return bell[n][0];
}

int main()
{
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    if(n >= 0 && n <= MAX)
    {
        printf("The Bell number is: %d\n", getBellNumber(n));
    }
    else
    {
        printf("Number out of range. Please input number between 0 and %d\n", MAX);
    }
    return 0;
}