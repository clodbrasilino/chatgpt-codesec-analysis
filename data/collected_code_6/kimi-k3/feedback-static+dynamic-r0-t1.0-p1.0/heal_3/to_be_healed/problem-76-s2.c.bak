#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1, got <no output>
  *  test case 1 failed: expected 5, got <no output>
  *  test case 0 failed: expected 20, got <no output>
  */

long long count_squares(long long m, long long n) {
    if (m <= 0 || n <= 0) {
        return 0;
    }
    
    if (m < n) {
        long long temp = m;
        m = n;
        n = temp;
    }
    
    return n * (n + 1) * (3 * m - n + 1) / 6;
}

int main(void) {
    long long m, n;
    
    if (scanf("%lld %lld", &m, &n) != 2) {
        return EXIT_FAILURE;
    }
    
    printf("%lld\n", count_squares(m, n));
    
    return EXIT_SUCCESS;
}