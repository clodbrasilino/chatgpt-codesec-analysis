#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (a < 0 || b < 0) return -1;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 255, got <no output>
  *  test case 2 failed: expected 6, got <no output>
  *  test case 0 failed: expected 12, got <no output>
  */

int lcm(int a, int b) {
    if (a < 0 || b < 0) return -1;
    int g = gcd(a, b);
    /* Possible weaknesses found:
     *  Assuming that condition 'g<0' is not redundant
     */
    if (g < 0) return -1;
    /* Possible weaknesses found:
     *  Division by zero
     *  Either the condition 'g<0' is redundant or there is division by zero at line 18. [zerodivcond]
     * UBSan: signed integer overflow: 515703239 * 6444 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1591,execs:637,op:havoc,rep:2)
     */
    return (a / g) * b;
}

int main() {
    int num1, num2;
    printf("Enter two positive integers: ");
    if (scanf("%d %d", &num1, &num2) != 2) {
        fprintf(stderr, "Invalid input. Please enter two integers.\n");
        return EXIT_FAILURE;
    }
    if (num1 <= 0 || num2 <= 0) {
        fprintf(stderr, "Both numbers must be positive.\n");
        return EXIT_FAILURE;
    }
    int result = lcm(num1, num2);
    if (result < 0) {
        fprintf(stderr, "Error in computation.\n");
        return EXIT_FAILURE;
    }
    printf("LCM of %d and %d is %d\n", num1, num2, result);
    return 0;
}