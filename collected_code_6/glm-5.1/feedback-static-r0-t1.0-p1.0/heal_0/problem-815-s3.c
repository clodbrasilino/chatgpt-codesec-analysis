#include <stdio.h>
#include <stdlib.h>

void sort_array(int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return;
    }
    size_t low = 0;
    size_t mid = 0;
    size_t high = size - 1;
    while (mid <= high) {
        switch (arr[mid]) {
            case 0:
                arr[mid] = arr[low];
                arr[low] = 0;
                low++;
                mid++;
                break;
            case 1:
                mid++;
                break;
            case 2:
                arr[mid] = arr[high];
                arr[high] = 2;
                high--;
                break;
            default:
                return;
        }
    }
}

int main(void) {
    int arr[] = {0, 2, 1, 2, 0, 1, 2, 1, 0};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    sort_array(arr, size);
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}