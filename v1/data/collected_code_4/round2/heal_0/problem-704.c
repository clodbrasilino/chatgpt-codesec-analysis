#include <stdio.h>

double harmonicSum(int n)
{
    double hSum = 0.0;
    for (int i = 1; i < n; i++)
    {
        if(i!=0) //to avoid division by zero
            hSum += 1.0 / i;
    }
    
    return hSum;
}
    
int main() 
{
    int n = 10;
    printf("%f\n", harmonicSum(n));
    return 0;
}