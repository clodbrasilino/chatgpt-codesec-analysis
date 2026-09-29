#include <stdio.h>

int minimum(int a, int b){
    return (a < b) ? a : b;
}

int main(){
    int num1, num2, min;

    printf("Enter first number: ");
    scanf("%d", &num1);  
    printf("Enter second number: ");
    scanf("%d", &num2);  

    min = minimum(num1, num2);

    printf("Minimum number is: %d\n", min);
    return 0;
}