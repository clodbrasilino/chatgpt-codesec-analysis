#include <stdio.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 0.56, got 3
  *  test case 0 failed: expected 0.54, got 3
  *  test case 1 failed: expected 0.69, got 5
  */

int positive_count(const int *array, size_t size) {
    int count = 0;
    for (size_t i = 0; i < size; i++) {
        if (array[i] > 0) {
            count++;
        }
    }
    return count;
}

double find_ratio(const int *array, size_t size) {
    if (size == 0) {
        return 0.0;
    }
    return positive_count(array, size) / (double)size;
}

int main(void) {
    const int arr1[] = {1, -2, 3, -4, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%.2f\n", find_ratio(arr1, size1));

    const int arr2[] = {-1, 2, -3, 4, -5, 6};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%.2f\n", find_ratio(arr2, size2));

    const int arr3[] = {0, 0, 7, 8, 9, 10, 11, 12, 13};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%.2f\n", find_ratio(arr3, size3));

    return 0;
}