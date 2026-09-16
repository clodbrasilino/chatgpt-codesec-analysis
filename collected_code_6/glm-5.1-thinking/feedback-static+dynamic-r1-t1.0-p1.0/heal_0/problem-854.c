#include <stdio.h>

void sift_down(int *arr, int size, int root) {
    while (1) {
        int smallest = root;
        int left = 2 * root + 1;
        int right = 2 * root + 2;

        if (left < size && arr[left] < arr[smallest]) {
            smallest = left;
        }

        if (right < size && arr[right] < arr[smallest]) {
            smallest = right;
        }

        if (smallest == root) {
            break;
        }

        int temp = arr[root];
        arr[root] = arr[smallest];
        arr[smallest] = temp;

        root = smallest;
    }
}

int heapify(int *arr, int size) {
    if (arr == NULL || size <= 0) {
        return -1;
    }

    for (int i = size / 2 - 1; i >= 0; i--) {
        sift_down(arr, size, i);
    }

    return 0;
}

int main(void) {
    int data[] = {12, 11, 13, 5, 6, 7};
    int size = sizeof(data) / sizeof(data[0]);

    if (heapify(data, size) == 0) {
        for (int i = 0; i < size; i++) {
            printf("%d ", data[i]);
        }
        printf("\n");
    }

    return 0;
}