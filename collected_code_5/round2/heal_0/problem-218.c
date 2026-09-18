#include<stdio.h>

int findMinOps(int num1, int num2){
    
    int result = 0;
    
    if(num1 < num2) {
       while(num1 != num2) {
           num1++;
           result++;
       }
    } 
    else if(num2 < num1) {
        while(num1 != num2) {
            num2++;
            result++;
        }
    }
    return result;
}

int main() {
   int num1, num2;
    
   printf("\nEnter the first number: ");
   scanf("%d", &num1);
    
   printf("Enter the second number: ");
   scanf("%d", &num2);
    
   printf("Minimum operations required to make two numbers equal: %d\n", findMinOps(num1, num2));
    
   return 0;
}