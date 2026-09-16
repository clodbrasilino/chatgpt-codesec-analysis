#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }

    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        heapify(arr, n, smallest);
    }
}

int replace_min(int arr[], int n, int new_val) {
    if (n <= 0) {
        return -1;
    }

    arr[0] = new_val;
    heapify(arr, n, 0);

    return 0;
}

void print_heap(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int heap[] = {3, 5, 9, 6, 8, 20, 10, 12, 18, 9};
    int n = sizeof(heap) / sizeof(heap[0]);

    int new_item = 7;

    if (replace_min(heap, n, new_item) == 0) {
        print_heap(heap, n);
    } else {
        printf("Heap is empty.\n");
    }

    return 0;
}