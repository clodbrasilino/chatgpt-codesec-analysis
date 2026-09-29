#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  *  test case 1 failed: expected False, got 1
  *  test case 2 failed: expected True, got 0
  */

int can_be_sum_of_powers_of_two(int n) {
    if (n <= 0) {
        return 0;
    }
    return (n & 1) != 0;
}

int main(void) {
    int number;
    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (can_be_sum_of_powers_of_two(number)) {
        printf("%d can be represented as sum of non-zero powers of 2.\n", number);
    } else {
        printf("%d cannot be represented as sum of non-zero powers of 2.\n", number);
    }
    return 0;
}