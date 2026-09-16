#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 4.5, got 4
  */

unsigned long long find_average_of_cubes(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    unsigned long long sum = (unsigned long long)n * (n + 1) / 2;
    sum *= sum;
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