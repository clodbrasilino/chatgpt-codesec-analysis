#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

int getLastDigit(int number) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
     */
    return abs(number % 10);
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    printf("The last digit is %d\n", getLastDigit(number));
    return 0;
}