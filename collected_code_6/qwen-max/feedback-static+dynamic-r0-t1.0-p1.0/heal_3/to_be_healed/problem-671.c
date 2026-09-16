#include <stdio.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 15, got 2147483643
  *  test case 2 failed: expected 15, got 2147483647
  *  test case 0 failed: expected 23, got 2147483637
  */

int set_right_most_unset_bit(int n) {
    return (n | (n + 1));
}

int main() {
    int number;
    printf("Enter an integer: ");
    if (scanf("%d", &number) != 1) {
        return 1;
    }
    int result = set_right_most_unset_bit(number);
    printf("Number after setting the right most unset bit: %d\n", result);
    return 0;
}