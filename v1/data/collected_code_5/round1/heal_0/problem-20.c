#include<stdio.h>
#include<math.h>

int isWoodall(int n)
{
    double result;
    int temp;
    for(int i = 1; i <= n; i++) {
        result = i * pow(2, i) - 1;
        temp = result;
        if(temp == n)
            return 1;
        if(temp > n)
            break;
    }
    return 0;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d",&n);
    if(isWoodall(n))
        printf("%d is a Woodall number.\n",n);
    else
        printf("%d is not a Woodall number.\n",n);
    return 0;
}