#include <stdio.h>
#include <stdlib.h>

void rearrange(int *arr, int size) {
    if (arr == NULL || size <= 1) {
        return;
    }

    int low = 0;
    int high = size - 1;

    while (low <= high) {
        if (arr[low] < 0) {
            int temp = arr[low];
            arr[low] = arr[high];
            arr[high--] = temp;
        } else {
            low++;
        }
    }
}

int main(void) {
    int arr[] = {-1, 2, -3, 4, 0, -5, 6, -7, 8, -9};
    int size = sizeof(arr) / sizeof(arr[0]);

    rearrange(arr, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}