#include <stdio.h>
#include <stdlib.h>

void rearrange(int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return;
    }

    size_t left = 0;
    size_t right = size - 1;

    while (left <= right) {
        while (left < size && arr[left] < 0) {
            left++;
        }

        while (right < size && arr[right] >= 0) {
            if (right == 0) {
                break;
            }
            right--;
        }

        if (left < right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }
}

int main(void) {
    int arr[] = {-1, 2, -3, 4, 5, 6, -7, 8, -9};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    rearrange(arr, size);

    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}