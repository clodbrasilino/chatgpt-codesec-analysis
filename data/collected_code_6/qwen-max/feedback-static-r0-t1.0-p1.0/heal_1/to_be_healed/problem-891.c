#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

int countDigits(int n) {
    if (n == 0) return 1;
    /* Possible weaknesses found:
     *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'abs'
     *  call to undeclared library function 'abs' with type 'int (int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    n = abs(n);
    return (int)(log10(n) + 1);
}

int haveSameNumberOfDigits(int a, int b) {
    return countDigits(a) == countDigits(b);
}

int main() {
    int num1, num2;
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    if (haveSameNumberOfDigits(num1, num2)) {
        printf("The numbers have the same number of digits.\n");
    } else {
        printf("The numbers do not have the same number of digits.\n");
    }

    return 0;
}