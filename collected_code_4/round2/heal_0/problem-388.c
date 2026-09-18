#include <stdio.h>

int highestPowerof2(int n) 
{
    int res = 0;
    
    for (int i=n; i>=1; i--)
    {
        if ((i & (i-1)) == 0)
        {
            res = i;
            break;
        }
    }
    
    return res;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    if(n<=0){
        printf("Enter a number greater than 0\n");
        return 0;
    }

    int highest_power= highestPowerof2(n);
    printf("The highest power of 2 less than or equal to %d is %d\n", n, highest_power);

    return 0;
}