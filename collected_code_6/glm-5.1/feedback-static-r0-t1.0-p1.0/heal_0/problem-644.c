#include <stdio.h>
#include <stdlib.h>

void reverse_array_upto(int *arr, size_t size, size_t pos) {
    if (arr == NULL || size == 0 || pos == 0) {
        return;
    }
    if (pos > size) {
        return;
    }
    size_t i = 0;
    size_t j = pos - 1;
    while (i < j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t pos = 5;

    reverse_array_upto(arr, size, pos);

    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}