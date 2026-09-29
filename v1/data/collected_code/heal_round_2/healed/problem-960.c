#include <stdio.h>
#include <stdlib.h>

int countWays(int n)
{
    int *tiles = (int*)calloc(n + 1, sizeof(int));
    if(tiles == NULL)
    {
        return -1;
    }

    tiles[0] = 1;
    tiles[1] = 1;

    for (int i = 2; i <= n; i++)
    {
     tiles[i] = tiles[i - 1] + tiles[i - 2];
    }
  
    int result = tiles[n];
    free(tiles);

    return result;
}

int main()
{
    int n;
    printf("Enter the width of the floor: ");
    if (scanf("%d", &n) != 1)
    {
        printf("Invalid input\n");
        return 1;
    }

    if(n >= 0)
    {
        int wayCount = countWays(n);
        if(wayCount == -1)
        {
            printf("Cannot calculate ways to tile the floor, out of memory.\n");
            return 1;
        }
        else
        {
            printf("Number of ways to tile the floor: %d\n", wayCount);
        }
    }
    else
    {
        printf("Width cannot be a negative number.\n");
        return 1;
    }

    return 0;
}