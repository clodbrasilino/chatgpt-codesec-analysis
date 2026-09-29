#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'sqrt'
  */

bool isDifferenceOfSquares(long n) {
    if (n < 0) return false;
    long x = 0, y = 1;
    /* Possible weaknesses found:
     *  include the header <math.h> or explicitly provide a declaration for 'sqrt'
     *  call to undeclared library function 'sqrt' with type 'double (double)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
     */
    long max_val = (long)sqrt((double)LONG_MAX);
    while (x <= y && y <= max_val) {
        long diff = y * y - x * x;
        if (diff == n) {
            return true;
        } else if (diff < n) {
            y++;
        } else {
            x++;
        }
    }
    return false;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (isDifferenceOfSquares(num)) {
        printf("Can be represented as difference of two squares.\n");
    } else {
        printf("Cannot be represented as difference of two squares.\n");
    }
    return 0;
}