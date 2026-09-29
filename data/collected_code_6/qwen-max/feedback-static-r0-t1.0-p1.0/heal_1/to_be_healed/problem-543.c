#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

int sum_digits(int a, int b) {
    int sum = a + b;
    /* Possible weaknesses found:
     *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'abs'
     *  call to undeclared library function 'abs' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    return (sum == 0) ? 1 : (int)log10(abs(sum)) + 1;
}

int main() {
    int num1 = 123;
    int num2 = 777;

    int digits = sum_digits(num1, num2);
    printf("The number of digits in the sum is: %d\n", digits);

    return 0;
}