#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1, got 0
  *  test case 0 failed: expected 20, got 12
  *  test case 1 failed: expected 5, got 3
  */

long long count_squares(int m, int n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }
    if (m > n) {
        int temp = m;
        m = n;
        n = temp;
    }
    long long a = m;
    long long b = n;
    return a * (a + 1) * (2 * b - a + 1) / 6;
}

int main() {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2) {
        return 1;
    }
    printf("%lld\n", count_squares(m, n));
    return 0;
}