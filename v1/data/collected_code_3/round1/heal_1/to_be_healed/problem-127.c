#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

int multiply(int a, int b) {
    int result = 0;
    /* Possible weaknesses found:
     *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
     */
    for(int i = 0; i < abs(b); i++) {
        result += a;
    }
    return b < 0 ? -result : result;
}

int main() {
    int a = 5;
    int b = 4;
    printf("The product of %d and %d is %d\n", a, b, multiply(a, b));
    return 0;
}