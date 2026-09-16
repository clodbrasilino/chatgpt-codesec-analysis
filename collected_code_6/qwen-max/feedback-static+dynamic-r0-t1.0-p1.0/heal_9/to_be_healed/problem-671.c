#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 15, got 11
  *  test case 0 failed: expected 23, got 21
  */

int set_right_most_unset_bit(int n) {
    if (n == INT_MAX || n == -1) return n;
    int unset_bit = (n + 1) & -(n + 1);
    if (unset_bit > 0)
        return n | (unset_bit >> 1);
    else
        return n;
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