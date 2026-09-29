#include <stdio.h>
#include <math.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'labs'
  */

int findFirstDigit(long num) {
    if (num == 0) return 0;
    /* Possible weaknesses found:
     *  include the header <stdlib.h> or explicitly provide a declaration for 'labs'
     *  call to undeclared library function 'labs' with type 'long (long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'labs' [-Wimplicit-function-declaration]
     */
    if (num < 0) num = labs(num);
    if (num > 0 && num < LONG_MAX) {
        int digits = (int)(log10(num) + 0.5);
        return (int)(num / pow(10, digits));
    }
    return -1; // Return -1 for invalid input
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    int firstDigit = findFirstDigit(number);
    if (firstDigit != -1) {
        printf("The first digit is %d\n", firstDigit);
    } else {
        printf("Invalid input\n");
    }
    return 0;
}