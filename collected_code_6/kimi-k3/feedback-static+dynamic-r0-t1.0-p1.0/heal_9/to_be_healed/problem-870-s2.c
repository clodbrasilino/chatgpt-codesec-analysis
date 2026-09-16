#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 48, got 0
  *  test case 1 failed: expected 50, got 0
  *  test case 2 failed: expected 522, got 0
  */

double sum_positive(const double *numbers, size_t count)
{
    double sum = 0.0;
    size_t i;

    if (numbers == NULL) {
        return 0.0;
    }

    for (i = 0; i < count; i++) {
        if (numbers[i] > 0.0) {
            sum += numbers[i];
        }
    }

    return sum;
}

int main(void)
{
    static const double test_numbers[] = {1.5, -2.0, 3.2, -4.8, 5.0};
    size_t count = sizeof(test_numbers) / sizeof(test_numbers[0]);
    double result = sum_positive(test_numbers, count);

    printf("%.2f\n", result);

    return 0;
}