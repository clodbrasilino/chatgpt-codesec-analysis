#include<stdio.h>

int sumOfSquares(int n){
    int sum = 0;
    for(int i = 0; i <= n; i++){
        if(i % 2 == 0){
            sum += i * i;
        }
    }
    return sum;
}

int main() {
    int n;
    
    printf("\nEnter the value of n: ");
    scanf("%d", &n);

    if(n < 0){
        printf("Error! Negative numbers not allowed!\n");
        return -1;
    }
    
    int result = sumOfSquares(n);
    
    printf("The Sum of squares of first %d even numbers is: %d\n", n, result);
    
    return 0;
}