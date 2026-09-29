#include <stdio.h>
#include <stdlib.h>

long long sum_of_squares(long long n) {
    return n * (n + 1) * (2 * n + 1) / 6;
}

long long sum_of_naturals(long long n) {
    return n * (n + 1) / 2;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 6, got 4
  *  test case 1 failed: expected 210, got 170
  *  test case 0 failed: expected 30, got 22
  */

long long difference(long long n) {
    long long sum_n = sum_of_naturals(n);
    long long sum_sq = sum_of_squares(n);
    long long sum_cubes = sum_n * sum_n;
    return sum_cubes - sum_sq;
}

int main(void) {
    long long n = 5;
    
    printf("%lld\n", difference(n));
    
    return 0;
}