#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 4.5, got <no output>
  *  test case 1 failed: expected 12, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

unsigned long long find_average_of_cubes(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    unsigned long long sum = 0;
    for (unsigned int i = 1; i <= n; i++) {
        sum += (unsigned long long)i * i * i;
    }
    return sum / n;
}

int main(void) {
    unsigned int n;
    if (scanf("%u", &n) != 1) {
        return 1;
    }
    unsigned long long avg = find_average_of_cubes(n);
    printf("%llu\n", avg);
    return 0;
}