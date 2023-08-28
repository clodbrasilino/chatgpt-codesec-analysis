#include<stdio.h>
 
int isEven(int num){
    if((num & 1) == 0)
        return 1;
    else
        return 0;
}
 
int main(){
    int number;
 
    printf("Enter a number: ");
    scanf("%d", &number);
 
    if(isEven(number))
        printf("%d is even\n", number);
    else
        printf("%d is odd\n", number);
 
    return 0;
}