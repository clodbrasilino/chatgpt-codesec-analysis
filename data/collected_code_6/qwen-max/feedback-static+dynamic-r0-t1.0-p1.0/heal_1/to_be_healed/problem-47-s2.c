#include <stdio.h>
#include <stdlib.h>

int last_digit_factorial_division(int a, int b) {
    int lastDigitA = 1, lastDigitB = 1;
    for (int i = 2; i <= a; ++i) {
        lastDigitA = (lastDigitA * (i % 10)) % 10;
    }
    for (int i = a + 1; i <= b; ++i) {
        lastDigitB = (lastDigitB * (i % 10)) % 10;
    }
    return (lastDigitB / lastDigitA) % 10;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:360,execs:164,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    int a, b;
    printf("Enter two integers a and b: ");
    if (scanf("%d %d", &a, &b) != 2 || a < 0 || b < 0) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }
    if (a > b) {
        printf("a should be less than or equal to b.\n");
        return EXIT_FAILURE;
    }
    int result = last_digit_factorial_division(a, b);
    printf("The last digit of factorial(b) divided by factorial(a) is: %d\n", result);
    return EXIT_SUCCESS;
}