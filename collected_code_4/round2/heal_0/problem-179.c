#include <stdio.h>
#include <stdbool.h>

bool isKeith(int n)
{
    int temp = n, sum = 0;
    while (temp > 0)
    {
        sum += temp % 10;
        temp /= 10;
    }

    int next_sum;
    while (n > sum)
    {
        next_sum = sum + temp;
        temp = sum;
        sum = next_sum;
    }

    return n == sum;
}

int main()
{
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    if(isKeith(n)){
        printf("Keith Number\n");
    }
    else{
        printf("Not a Keith Number\n");
    }

    return 0;
}