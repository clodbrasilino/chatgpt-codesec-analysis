#include <stdio.h>
#include <stdlib.h>

int countWays(int n)
{
    int tiles[n + 1];
    tiles[0] = 0;
    tiles[1] = 1;
    tiles[2] = 2;
    for (int i = 3; i <= n; i++)
    {
        tiles[i] = tiles[i - 1] + tiles[i - 2];
    }
    return tiles[n];
}

int main()
{
    int n;
    printf("Enter the width of the floor: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);
    printf("Number of ways to tile the floor: %d\n", countWays(n));
    return 0;
}