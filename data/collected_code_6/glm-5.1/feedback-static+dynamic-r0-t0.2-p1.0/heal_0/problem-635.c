#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void push(int *heap, int *size, int value) {
    heap[*size] = value;
    int current = *size;
    while (current > 0) {
        int parent = (current - 1) / 2;
        if (heap[current] < heap[parent]) {
            swap(&heap[current], &heap[parent]);
            current = parent;
        } else {
            break;
        }
    }
    (*size)++;
}

int pop(int *heap, int *size) {
    if (*size == 0) {
        exit(EXIT_FAILURE);
    }
    int min_val = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    int current = 0;
    while (1) {
        int left = 2 * current + 1;
        int right = 2 * current + 2;
        int smallest = current;
        if (left < *size && heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < *size && heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest != current) {
            swap(&heap[current], &heap[smallest]);
            current = smallest;
        } else {
            break;
        }
    }
    return min_val;
}

void heap_sort(int *values, int count) {
    if (count <= 0) {
        return;
    }
    int *heap = (int *)malloc(count * sizeof(int));
    if (heap == NULL) {
        exit(EXIT_FAILURE);
    }
    int heap_size = 0;
    for (int i = 0; i < count; i++) {
        push(heap, &heap_size, values[i]);
    }
    for (int i = 0; i < count; i++) {
        values[i] = pop(heap, &heap_size);
    }
    free(heap);
}

int main(void) {
    int values[] = {42, 12, 18, 5, 9, 23, 7, 61};
    int count = sizeof(values) / sizeof(values[0]);
    heap_sort(values, count);
    for (int i = 0; i < count; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");
    return 0;
}