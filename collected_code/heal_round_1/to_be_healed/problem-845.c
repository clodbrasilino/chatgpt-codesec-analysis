#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'log10'
  */

int countDigitsInFactorial(int n) {
    if (n < 0) {
        printf("Invalid input. Number must be non-negative.\n");
        return -1;
    }

    if (n <= 1) {
        return 1;
    }

    double digits = 0;
    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         *  include '<math.h>' or provide a declaration of 'log10'
         *  implicit declaration of function 'log10' [-Wimplicit-function-declaration]
         *  incompatible implicit declaration of built-in function 'log10' [-Wbuiltin-declaration-mismatch]
         */
        digits += log10(i);
    }

    return (int)(digits) + 1;
}

int main() {
    int num;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'num' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &num);

    int result = countDigitsInFactorial(num);
    if (result != -1) {
        printf("Number of digits in factorial of %d is %d\n", num, result);
    }

    return 0;
}