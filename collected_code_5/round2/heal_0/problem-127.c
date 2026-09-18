#include<stdio.h>

int multiply(int a, int b){
    int result = 0;
    int x = (a > 0)? a : -a;
    int y = (b > 0)? b : -b;

    while(y > 0){
        if(y & 1) result += x;

        x <<= 1;
        y >>= 1;
    }
    return ((a < 0) ^ (b < 0))? -result : result;
}

int main(){
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);
    
    printf("Multiplication of %d and %d is %d", a, b, multiply(a, b));
    return 0;
}