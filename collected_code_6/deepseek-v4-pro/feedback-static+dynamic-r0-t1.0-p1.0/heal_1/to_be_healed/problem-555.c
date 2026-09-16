#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 210, got <no output>
  *  test case 0 failed: expected 30, got <no output>
  *  test case 2 failed: expected 6, got <no output>
  */

long long difference(long long n) {
    long long sum_n = n * (n + 1) / 2;
    long long sum_cubes = sum_n * sum_n;
    return sum_cubes - sum_n;
}

int main(void) {
    long long n;
    
    printf("Enter a natural number: ");
    if (scanf("%lld", &n) != 1 || n < 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("Difference: %lld\n", difference(n));
    
    return 0;
}