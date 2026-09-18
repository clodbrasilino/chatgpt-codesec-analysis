#include <stdio.h> 

int eulerian(int n, int m)
{
    if (m >= n || n == 0)
        return 0;
    if (m == 0)
        return 1;

    return ((n - m) * eulerian(n - 1, m - 1) + 
           (m + 1) * eulerian(n - 1, m));
}

int main()
{
    int n, m;

    printf("Enter the values for n and m:");
    scanf("%d %d", &n, &m);

    printf("The eulerian number a(%d, %d) is %d", n, m, eulerian(n, m));

    return 0;
}