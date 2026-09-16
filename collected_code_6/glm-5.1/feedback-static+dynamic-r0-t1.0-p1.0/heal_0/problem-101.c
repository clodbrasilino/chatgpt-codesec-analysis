#include <stdio.h>
#include <stdlib.h>

int find_kth_element(const int *array, size_t size, size_t k) {
    if (array == NULL || size == 0 || k >= size) {
        return -1;
    }
    return array[k];
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t k = 2;

    int result = find_kth_element(arr, size, k);
    printf("%d\n", result);

    return 0;
}