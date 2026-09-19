#include <stdio.h>
#include <math.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'labs'
  */

int findFirstDigit(long num) {
    /* Possible weaknesses found:
     *  implicit declaration of function 'labs' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'labs' with type 'long (long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'labs'
     */
    if (num < 0) num = labs(num);
    if (num == 0) return 0;
    if (num == LONG_MAX) return 9;

    int digits = 0;
    long n = num;
    while (n >= 10) {
        n /= 10;
        digits++;
    }
    return (int)(num / powl(10.0L, digits));
}

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    int firstDigit = findFirstDigit(number);
    printf("The first digit is %d\n", firstDigit);
    return 0;
}