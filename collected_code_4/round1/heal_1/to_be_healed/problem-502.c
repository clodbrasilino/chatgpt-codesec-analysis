#include <stdio.h>
 /* Possible weaknesses found:
  *  'remainder' is declared in header '<math.h>'
  */

/* Possible weaknesses found:
 *  conflicting types for built-in function 'remainder'; expected 'double(double,  double)' [-Wbuiltin-declaration-mismatch]
 */
int remainder(int num1, int num2) {
    if (num2 == 0) {
        printf("Error: Division by zero is undefined.\n");
        return -1;
    }
    return num1 % num2;
}

int main() {
    int num1, num2;
    printf("Enter the first number: ");
    scanf("%d", &num1);
    printf("Enter the second number: ");
    scanf("%d", &num2);

    int result = remainder(num1, num2);

    if (result != -1) {
        printf("The remainder of the division is %d\n", result);
    }

    return 0;
}