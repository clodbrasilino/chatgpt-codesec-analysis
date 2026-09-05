#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_down(int *heap, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] < heap[smallest])
        smallest = left;

    if (right < size && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify_down(heap, size, smallest);
    }
}

void heapify_up(int *heap, int i) {
    int parent = (i - 1) / 2;
    if (i > 0 && heap[i] < heap[parent]) {
        swap(&heap[i], &heap[parent]);
        heapify_up(heap, parent);
    }
}

void delete_min_and_insert(int *heap, int *size, int *capacity, int new_item) {
    if (*size == 0) {
        if (*size >= *capacity) {
            int new_capacity = (*capacity == 0) ? 1 : *capacity * 2;
            int *temp = (int *)realloc(heap, new_capacity * sizeof(int));
            if (temp == NULL) {
                exit(EXIT_FAILURE);
            }
            heap = temp;
            *capacity = new_capacity;
        }
        heap[*size] = new_item;
        (*size)++;
        heapify_up(heap, *size - 1);
        return;
    }

    heap[0] = new_item;
    heapify_down(heap, *size, 0);
}

int main() {
    int capacity = 10;
    int size = 0;
    int *heap = (int *)malloc(capacity * sizeof(int));
    if (heap == NULL) {
        return EXIT_FAILURE;
    }

    int initial_data[] = {3, 5, 8, 10, 12};
    for (int i = 0; i < sizeof(initial_data) / sizeof(initial_data[0]); i++) {
        heap[size] = initial_data[i];
        size++;
        heapify_up(heap, size - 1);
    }

    delete_min_and_insert(heap, &size, &capacity, 4);

    for (int i = 0; i < size; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");

    free(heap);

    return 0;
}