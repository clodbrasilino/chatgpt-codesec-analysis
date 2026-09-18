#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_ARRAYS 100

struct Element {
    int value;
    int array_idx;
    int element_idx;
};

void swap(struct Element* a, struct Element* b) {
    struct Element temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct Element heap[], int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].value < heap[smallest].value) {
        smallest = left;
    }
    if (right < size && heap[right].value < heap[smallest].value) {
        smallest = right;
    }
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, size, smallest);
    }
}

void buildMinHeap(struct Element heap[], int size) {
    for (int i = (size - 1) / 2; i >= 0; i--) {
        minHeapify(heap, size, i);
    }
}

void findSmallestRange(int** arrays, int k, const int* array_sizes) {
    if (arrays == NULL || array_sizes == NULL || k <= 0) {
        return;
    }

    struct Element* heap = (struct Element*)malloc(k * sizeof(struct Element));
    if (heap == NULL) {
        return;
    }

    int current_max = INT_MIN;
    for (int i = 0; i < k; i++) {
        if (array_sizes[i] == 0) {
            free(heap);
            return;
        }
        heap[i].value = arrays[i][0];
        heap[i].array_idx = i;
        heap[i].element_idx = 0;
        if (heap[i].value > current_max) {
            current_max = heap[i].value;
        }
    }

    buildMinHeap(heap, k);

    int min_range = INT_MAX;
    int range_start = 0;
    int range_end = 0;

    while (1) {
        struct Element min_element = heap[0];

        if (current_max - min_element.value < min_range) {
            min_range = current_max - min_element.value;
            range_start = min_element.value;
            range_end = current_max;
        }

        min_element.element_idx++;
        if (min_element.element_idx >= array_sizes[min_element.array_idx]) {
            break;
        }

        min_element.value = arrays[min_element.array_idx][min_element.element_idx];
        if (min_element.value > current_max) {
            current_max = min_element.value;
        }

        heap[0] = min_element;
        minHeapify(heap, k, 0);
    }

    printf("Smallest range is [%d, %d]\n", range_start, range_end);
    free(heap);
}

int main(void) {
    int arr1[] = {4, 7, 9, 12, 15};
    int arr2[] = {0, 8, 10, 14, 20};
    int arr3[] = {6, 12, 16, 30, 50};

    int* arrays[] = {arr1, arr2, arr3};
    const int sizes[] = {
        sizeof(arr1) / sizeof(arr1[0]),
        sizeof(arr2) / sizeof(arr2[0]),
        sizeof(arr3) / sizeof(arr3[0])
    };
    int k = sizeof(arrays) / sizeof(arrays[0]);

    findSmallestRange(arrays, k, sizes);

    return 0;
}