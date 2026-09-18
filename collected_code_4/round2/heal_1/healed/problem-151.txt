#include <stdio.h>

int gcd(int a, int b){
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

int isCop(int a, int b){
    return gcd(a,b) == 1;
}

int main(){
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);
    if(isCop(a, b))
        printf("The numbers are coprime\n");
    else
        printf("The numbers are not coprime\n");
    return 0;
}