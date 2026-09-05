#include <stdio.h>
#include <stdlib.h>

void reverse_upto(int *arr, int size, int pos) {
    if (arr == NULL || size <= 0 || pos < 0) {
        return;
    }
    if (pos >= size) {
        pos = size - 1;
    }
    int start = 0;
    int end = pos;
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void print_array(const int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    print_array(arr, size);

    reverse_upto(arr, size, 4);
    print_array(arr, size);

    reverse_upto(arr, size, 9);
    print_array(arr, size);

    reverse_upto(arr, size, -1);
    print_array(arr, size);

    reverse_upto(NULL, size, 4);

    return 0;
}