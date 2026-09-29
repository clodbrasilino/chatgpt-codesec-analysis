#include <stdio.h>
#include <math.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'labs'
  */

void addAndPrintDigits(long a, long b) {
    long sum = a + b;
    if (sum < INT_MIN || sum > INT_MAX) {
        printf("Sum: Overflow, Number of Digits: N/A\n");
        return;
    }
    /* Possible weaknesses found:
     *  implicit declaration of function 'labs' [-Wimplicit-function-declaration]
     *  call to undeclared library function 'labs' with type 'long (long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'labs'
     */
    int digits = (sum == 0) ? 1 : (int) log10(labs(sum)) + 1;
    printf("Sum: %ld, Number of Digits: %d\n", sum, digits);
}

int main() {
    int num1, num2;

    printf("Enter first number: ");
    if (scanf("%d", &num1) != 1) return 1;

    printf("Enter second number: ");
    if (scanf("%d", &num2) != 1) return 2;

    addAndPrintDigits(num1, num2);

    return 0;
}