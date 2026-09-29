#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void max_heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        max_heapify(arr, n, largest);
    }
}

void min_heapify(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        min_heapify(arr, n, smallest);
    }
}

void build_max_heap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        max_heapify(arr, n, i);
}

void build_min_heap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        min_heapify(arr, n, i);
}

int maximum_product_of_three(const int arr[], int n) {
    if (n < 3) {
        fprintf(stderr, "Array must have at least 3 elements\n");
        exit(EXIT_FAILURE);
    }

    int *max_heap = (int *)malloc(n * sizeof(int));
    int *min_heap = (int *)malloc(n * sizeof(int));

    if (!max_heap || !min_heap) {
        fprintf(stderr, "Memory allocation failed\n");
        free(max_heap);
        free(min_heap);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        max_heap[i] = arr[i];
        min_heap[i] = arr[i];
    }

    build_max_heap(max_heap, n);
    build_min_heap(min_heap, n);

    int max1 = max_heap[0];
    swap(&max_heap[0], &max_heap[n - 1]);
    max_heapify(max_heap, n - 1, 0);
    int max2 = max_heap[0];
    swap(&max_heap[0], &max_heap[n - 2]);
    max_heapify(max_heap, n - 2, 0);
    int max3 = max_heap[0];

    int min1 = min_heap[0];
    swap(&min_heap[0], &min_heap[n - 1]);
    min_heapify(min_heap, n - 1, 0);
    int min2 = min_heap[0];

    free(max_heap);
    free(min_heap);

    int product1 = max1 * max2 * max3;
    int product2 = min1 * min2 * max1;

    return product1 > product2 ? product1 : product2;
}

int main(void) {
    int arr[] = {-10, -10, 5, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = maximum_product_of_three(arr, n);
    printf("Maximum product: %d\n", result);

    return 0;
}