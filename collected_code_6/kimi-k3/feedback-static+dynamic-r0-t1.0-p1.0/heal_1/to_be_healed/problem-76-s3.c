#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 5, got <no output>
  *  test case 0 failed: expected 20, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

long long count_squares(int m, int n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }
    long long total = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            total += (m - i + 1) * (n - j + 1);
        }
    }
    return total;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:30200,execs:672,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2) {
        return 1;
    }
    printf("%lld\n", count_squares(m, n));
    return 0;
}