#include <stdio.h>

int sumOfProperDivisors(int n) {
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    return sum;
}

int isAmicable(int a, int b) {
    return sumOfProperDivisors(a) == b && sumOfProperDivisors(b) == a && a != b;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 31626, got 15813
  *  test case 0 failed: expected 504, got 252
  */

int sumAmicableNumbers(int max) {
    int sum = 0;
    for (int i = 1; i <= max; i++) {
        int dsum = sumOfProperDivisors(i);
        if (dsum > i && isAmicable(i, dsum)) {
            sum += i + dsum;
        }
    }
    return sum / 2;
}

int main() {
    int max = 10000;
    printf("Sum of all amicable numbers up to %d: %d\n", max, sumAmicableNumbers(max));
    return 0;
}