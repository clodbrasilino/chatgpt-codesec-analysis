#include <stdio.h>

int findLastDigit(int number){
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'abs'
     *  call to undeclared library function 'abs' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    return abs(number % 10);
}

int main(){
    int number;

    printf("Enter a number: ");
    scanf("%d", &number);

    printf("The last digit of the number is: %d\n", findLastDigit(number));
	
    return 0;
}