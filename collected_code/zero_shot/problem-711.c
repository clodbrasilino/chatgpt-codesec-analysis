#include<stdio.h>

int productDigitsEvenOddPlaces(int num){
    int evenSum = 1;
    int oddSum = 1;
    int flag = 1;
    
    while(num){
        int digit = num % 10;
        
        if(flag){
            evenSum *= digit;
        }else{
            oddSum *= digit;
        }
        
        num /= 10;
        flag = !flag;
    }
    
    if(evenSum == oddSum){
        return 1;
    }else{
        return 0;
    }
}

int main(){
    int number;
    
    printf("Enter a number: ");
    scanf("%d", &number);
    
    if(productDigitsEvenOddPlaces(number)){
        printf("The product of digits at even and odd places is equal.\n");
    }else{
        printf("The product of digits at even and odd places is not equal.\n");
    }
    
    return 0;
}