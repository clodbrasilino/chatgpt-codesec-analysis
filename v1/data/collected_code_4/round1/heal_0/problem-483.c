#include <stdio.h>

unsigned long long factorial(int n){
    if(n==0 || n==1){
        return 1;
    }else{
        return n*factorial(n-1);
    }
}

int findFirstFactorialDivisibleByX(int x){
    int i = 0;
    while(1){
        if(factorial(i)%x==0){
            return i;
        }
        i++;
    }
}

int main(){
   int x;
   printf("Enter a number: ");
   scanf("%d", &x);
   printf("The first natural number whose factorial is divisible by %d is %d\n", x, findFirstFactorialDivisibleByX(x));
   return 0;
} 