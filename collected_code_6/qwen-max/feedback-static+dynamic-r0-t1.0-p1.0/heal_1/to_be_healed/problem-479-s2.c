#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  *  test case 1 failed: expected 4, got <no output>
  */

int get_first_digit(long n) {
    if (n == 0) return 0;
    n = (n < 0) ? -n : n; 
    while (n >= 10) {
        n /= 10;
    }
    return n;
}

int main() {
    long number = 12345;
    int first_digit = get_first_digit(number);
    printf("First digit: %d\n", first_digit);
    return 0;
}