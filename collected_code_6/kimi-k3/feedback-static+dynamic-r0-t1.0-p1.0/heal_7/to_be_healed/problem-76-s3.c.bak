#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 5, got 9
  *  test case 0 failed: expected 20, got 60
  */

long long count_squares(int m, int n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }
    long long a = m;
    long long b = n;
    return a * (a + 1) * b * (b + 1) / 4;
}

int main() {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2) {
        return 1;
    }
    printf("%lld\n", count_squares(m, n));
    return 0;
}