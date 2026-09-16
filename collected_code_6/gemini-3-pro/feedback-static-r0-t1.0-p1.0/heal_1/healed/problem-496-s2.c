#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void minHeapify(int heap[], int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] < heap[smallest]) {
        smallest = left;
    }

    if (right < size && heap[right] < heap[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, size, smallest);
    }
}

void buildMinHeap(int heap[], int size) {
    for (int i = (size / 2) - 1; i >= 0; i--) {
        minHeapify(heap, size, i);
    }
}

int extractMin(int heap[], int *size) {
    if (*size <= 0) {
        return -1; 
    }
    
    if (*size == 1) {
        (*size)--;
        return heap[0];
    }

    int root = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    minHeapify(heap, *size, 0);

    return root;
}

int* findKSmallest(const int arr[], int n, int k) {
    if (n <= 0 || k <= 0 || k > n) {
        return NULL;
    }

    int *heap = (int *)malloc(n * sizeof(int));
    if (heap == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        heap[i] = arr[i];
    }

    buildMinHeap(heap, n);

    int *result = (int *)malloc(k * sizeof(int));
    if (result == NULL) {
        free(heap);
        return NULL;
    }

    int heapSize = n;
    for (int i = 0; i < k; i++) {
        result[i] = extractMin(heap, &heapSize);
    }

    free(heap);
    return result;
}

int main(void) {
    int arr[] = {12, 3, 5, 7, 19, 2, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    int *smallestNumbers = findKSmallest(arr, n, k);

    if (smallestNumbers != NULL) {
        for (int i = 0; i < k; i++) {
            printf("%d ", smallestNumbers[i]);
        }
        printf("\n");
        free(smallestNumbers);
    } else {
        printf("Error allocating memory or invalid input.\n");
        return 1;
    }

    return 0;
}