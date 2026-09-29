#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 50, got <no output>
  *  test case 0 failed: expected 48, got <no output>
  *  test case 2 failed: expected 522, got <no output>
  */

int sum_positive(const int *array, size_t size) {
    if (array == NULL) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] > 0) {
            if (array[i] > INT_MAX - sum) {
                return 0;
            }
            sum += array[i];
        }
    }
    return sum;
}

int main(void) {
    int data[] = {-3, 5, -2, 12, 0, -8, 7};
    size_t data_size = sizeof(data) / sizeof(data[0]);

    int result = sum_positive(data, data_size);
    printf("%d\n", result);

    return 0;
}