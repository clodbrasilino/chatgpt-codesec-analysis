#include <stdio.h>
#include <stdbool.h>

bool checkEven(int num){
    return num % 2 == 0;
}

int main(){
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    
    if(checkEven(num)){
       printf("The number is even.\n");
    }
    else {
       printf("The number is not even.\n");
    }
    
    return 0;
}