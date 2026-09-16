#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 24, got 9
  *  test case 1 failed: expected 13, got 4
  */

int sum_odd_factors(int n) {
    int sum = 0;
    if (n <= 0) return 0;
    for (int i = 1; i * i <= n; i += 2) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                int quotient = n / i;
                if (quotient % 2 != 0) {
                    sum += quotient;
                }
            }
        }
    }
    return sum;
}

int main() {
    int num = 45;
    printf("Sum of odd factors of %d is %d\n", num, sum_odd_factors(num));
    return 0;
}