#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

int last_digit(int num) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'abs'
     *  call to undeclared library function 'abs' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    return abs(num) % 10;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) == 1) {
        int result = last_digit(number);
        printf("The last digit of %d is %d\n", number, result);
    } else {
        printf("Invalid input. Please enter an integer.\n");
    }
    return 0;
}