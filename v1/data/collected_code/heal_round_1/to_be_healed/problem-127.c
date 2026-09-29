#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'abs'
  */

int multiply(int num1, int num2) {
    int result = 0;

    if (num1 == 0 || num2 == 0) {
        return 0;
    }

    int sign = ((num1 < 0) ^ (num2 < 0)) ? -1 : 1;

    /* Possible weaknesses found:
     *  implicit declaration of function 'abs' [-Wimplicit-function-declaration]
     */
    num1 = abs(num1);
    num2 = abs(num2);

    while (num2 > 0) {
        if (num2 & 1) {
            result += num1;
        }

        num1 <<= 1;
        num2 >>= 1;
    }

    return sign * result;
}

int main() {
    int num1, num2;

    printf("Enter two numbers: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'num2' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'num1' is initialized [premium-bughuntingUninit]
     */
    scanf("%d %d", &num1, &num2);

    int result = multiply(num1, num2);

    printf("Result: %d\n", result);

    return 0;
}