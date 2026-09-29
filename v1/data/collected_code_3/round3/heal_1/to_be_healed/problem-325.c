#include <stdio.h>
#include <limits.h>

int minSquares(int n)
{
    if (n <= 3)
        return n;

    int res = n;

    for (int x = 1; x <= n; x++) {
        int temp = x * x;
        if (temp > n)
            break;
        else
            /* Possible weaknesses found:
             *  implicit declaration of function 'min' [-Wimplicit-function-declaration]
             */
            res = min(res, 1 + minSquares(n - temp));
    }
    return res;
}

int main()
{
    int n = 6;
    printf("Minimum number of squares whose sum is equal to %d is %d", n, minSquares(n));
    return 0;
}