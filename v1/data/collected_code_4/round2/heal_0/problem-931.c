#include <stdio.h>

long long cubeSum(int n){
    long long sum = 0;

    for(int i=1; i<=n; ++i)
        sum += (long long)i*i*i;

    return sum;
}

int main(){
   int number;
   printf("Enter a positive integer: ");
   scanf("%d", &number);
   
   if(number<0){
        printf("Please enter a positive integer next time.");
        return 1; // Return error code
   }

   long long sum = cubeSum(number);

   printf("The sum of series up to the entered number is %lld", sum);
   
   return 0;
}