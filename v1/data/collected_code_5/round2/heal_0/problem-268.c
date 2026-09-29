#include<stdio.h>

long long calculateStarNumber(int n){
    if(n <= 0) {
        return -1;
    }

    return 6 * n * (n-1) + 1;
}

int main()
{
    int n;
    printf("Enter a number: ");
    scanf("%d",&n);
    long long result = calculateStarNumber(n);

    if(result < 0) {
       printf("Input must be a positive integer\n");
    }
    else {
       printf("The %d'th Star Number: %lld\n", n, result);
    }

    return 0;
}