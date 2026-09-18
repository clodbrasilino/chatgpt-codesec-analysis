#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 50, got 0
  *  test case 0 failed: expected 48, got 0
  *  test case 2 failed: expected 522, got 0
  */

double sum_positive(const double *numbers, size_t count) {
    double sum = 0.0;
    for (size_t i = 0; i < count; ++i) {
        if (numbers[i] > 0.0) {
            sum += numbers[i];
        }
    }
    return sum;
}

int main(void) {
    double numbers[] = {-1.5, 3.0, 2.5, 0.0, -4.0, 5.5};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    double result = sum_positive(numbers, count);
    printf("%.2f\n", result);
    return 0;
}