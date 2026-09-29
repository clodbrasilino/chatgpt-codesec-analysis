#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 0, got <no output>
  *  test case 0 failed: expected 3, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  */

int last_digit(int num) {
    return abs(num) % 10;
}

int main() {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) == 1) {
        int result = last_digit(number);
        printf("The last digit of %d is %d\n", number, result);
    } else {
        printf("Invalid input. Please enter an integer.\n");
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (getchar() != '\n');  // Clear input buffer
    }
    return 0;
}