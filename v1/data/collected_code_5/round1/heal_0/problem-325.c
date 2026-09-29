#include <stdio.h>
#include <limits.h>

int getMinSquares(unsigned int n)
{
    if(n <= 3)
        return n;
     
    int res = n;
    
    for (int x = 1; x <= n; x++)
    {
        int temp = x*x;
        if (temp > n)
            break;
        else
            res = (res < getMinSquares(n - temp)) ? res : getMinSquares(n - temp);
    }
    return res;
}

int main()
{
    int n = 13;
    printf("Minimum number of squares is %d", getMinSquares(n));
    return 0;
}