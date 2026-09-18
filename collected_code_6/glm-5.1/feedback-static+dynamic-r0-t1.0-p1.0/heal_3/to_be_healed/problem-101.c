#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 8, got 0
  *  test case 2 failed: expected 36, got 25
  */

int find_kth_element(const int *array, size_t size, size_t k) {
    if (array == NULL || size == 0 || k >= size) {
        return -1;
    }
    return array[k];
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t k1 = 2;
    size_t k2 = 3;

    int result1 = find_kth_element(arr, size, k1);
    int result2 = find_kth_element(arr, size, k2);
    
    printf("%d\n", result1);
    printf("%d\n", result2);

    return 0;
}