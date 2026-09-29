#include <stdio.h>
#include <math.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 513, got 905787
  *  test case 0 failed: expected 243, got 13941
  */

int round_and_sum(const double *numbers, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += pow(round(numbers[i]), 3);
    }
    return sum;
}

int main() {
    double numbers[] = {12.5, 13.3, 14.7, 15.2};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int result = round_and_sum(numbers, length);
    printf("%d\n", result);
    return 0;
}