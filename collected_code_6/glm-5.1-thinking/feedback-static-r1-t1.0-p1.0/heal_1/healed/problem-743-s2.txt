#include <stdio.h>
#include <stddef.h>

static void reverse(int *arr, size_t start, size_t end) {
    size_t left = start;
    size_t right = end - 1;
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }
}

void rotate_right(int *arr, size_t length, size_t k) {
    if (arr == NULL || length == 0) {
        return;
    }
    k = k % length;
    if (k == 0) {
        return;
    }
    reverse(arr, 0, length);
    reverse(arr, 0, k);
    reverse(arr, k, length);
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5, 6, 7};
    size_t len = sizeof(data) / sizeof(data[0]);
    size_t rotations = 3;

    rotate_right(data, len, rotations);

    for (size_t i = 0; i < len; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    return 0;
}