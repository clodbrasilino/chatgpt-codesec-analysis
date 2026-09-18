#include <stdio.h>
#include <math.h>

int decimalToInteger(double num){
    double decimal = num - (int)num;
    if(decimal >= 0.5) return (int)num + 1;
    else return (int)num;
}

int checkProductOfSquares(int num){
    int i, j;
    for(i = 0; i*i <= num; i++){
        for(j = 0; j*j <= num; j++){
            if(i*i * j*j == num){
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    int num;
    printf("Enter a number:\n");
    scanf("%d", &num);

    if(num < 0 ){
        printf("Number is negative. Please enter a positive number.\n");
        return 0;
    } 

    int result = checkProductOfSquares(num);

    if(result == 1){
        printf("The number can be represented as a product of two squares.\n");
    } else {
        printf("The number cannot be represented as a product of two squares.\n");
    }
    return 0;
}