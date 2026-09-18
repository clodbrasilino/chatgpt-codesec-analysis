#include<stdio.h>

int gcd(int a, int b){
    if(b == 0)
        return a;
    else
        return gcd(b, a % b);
}

int lcm(int a, int b){
    int temp = (a > b) ? a : b;
    temp = temp / gcd(a, b);

    return temp * ((a > b) ? b : a);
}

int main(){
    int num1, num2;

    printf("Enter two positive integers: ");
    scanf("%d %d", &num1, &num2);

    printf("\nLCM of %d and %d = %d\n", num1, num2, lcm(num1, num2));

    return 0;
}