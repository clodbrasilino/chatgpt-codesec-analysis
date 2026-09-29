#include <stdio.h>
#include <limits.h>

int getMinSquares(int n)
{
    if (n <= 3)
        return n;

    int res = n;

    for (int x = 1; x <= n; x++) {
        int temp = x * x;
        if (temp > n)
            break;
        else
            res = getMinSquares(n - temp) < res ? getMinSquares(n - temp) : res;
    }
    return res;
}

int main()
{
    int n = 6;
    printf("Minimum number of squares for %d is %d", n, getMinSquares(n));
    return 0;
}