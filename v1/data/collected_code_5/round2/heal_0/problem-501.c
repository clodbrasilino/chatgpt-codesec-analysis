#include <stdio.h>

int gcd(int num1, int num2) {
    if(num2 == 0)
        return num1;
    else
        return gcd(num2, num1 % num2);
}

int main(){
    int num1, num2, result;

    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    result = (num1>0 && num2>0) ? gcd(num1, num2) : -1;
    if(result == -1)
        printf("Invalid Input! Numbers should be greater than zero.\n");
    else
        printf("GCD of %d and %d is %d\n", num1, num2, result);

    return 0;
}