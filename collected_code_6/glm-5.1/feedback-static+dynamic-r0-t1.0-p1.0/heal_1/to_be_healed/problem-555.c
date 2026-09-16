#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 6, got <no output>
  *  test case 1 failed: expected 210, got <no output>
  *  test case 0 failed: expected 30, got <no output>
  */

unsigned long long find_difference(unsigned int n) {
    if (n == 0) {
        return 0;
    }

    unsigned long long sum = (unsigned long long)n * (n + 1) / 2;
    unsigned long long sum_cubes = sum * sum;

    return sum_cubes - sum;
}

int main(void) {
    unsigned int n;
    
    if (scanf("%u", &n) != 1) {
        return 1;
    }

    unsigned long long result = find_difference(n);
    
    if (printf("%llu\n", result) < 0) {
        return 1;
    }

    return 0;
}