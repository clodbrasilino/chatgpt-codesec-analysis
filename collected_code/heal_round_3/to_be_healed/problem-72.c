#include <stdio.h>
#include <stdbool.h>
#include <math.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

bool isDifferenceOfSquares(int num) {
    for (int i = 0; i * i <= num; ++i) {
        int diff = num - i * i;
        /* Possible weaknesses found:
         *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
         */
        int sqrtDiff = (int)sqrt(abs(diff));
        if (sqrtDiff * sqrtDiff == diff) {
            return true;
        }
    }
    return false;
}

int main() {
    int number = 0;
    printf("Enter a number: ");
    scanf("%d", &number);

    if (isDifferenceOfSquares(number)) {
        printf("%d can be represented as difference of two squares.\n", number);
    } else {
        printf("%d cannot be represented as difference of two squares.\n", number);
    }

    return 0;
}