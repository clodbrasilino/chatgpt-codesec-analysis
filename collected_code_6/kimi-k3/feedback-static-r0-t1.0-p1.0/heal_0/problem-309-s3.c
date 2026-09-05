#include <stdio.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int main(void)
{
    int x = 10;
    int y = 20;
    int result = max(x, y);
    
    printf("Maximum of %d and %d is %d\n", x, y, result);
    
    return 0;
}