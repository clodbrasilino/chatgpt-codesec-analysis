#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

int find_last_digit(int number) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'abs'
     *  call to undeclared library function 'abs' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    return abs(number) % 10;
}

int main() {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Input error\n");
        return 1;
    }
    int last_digit = find_last_digit(num);
    printf("The last digit is: %d\n", last_digit);
    return 0;
}