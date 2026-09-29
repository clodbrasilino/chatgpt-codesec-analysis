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
        fprintf(stderr, "Heap underflow\n");
        exit(EXIT_FAILURE);
    }
    int min_value = heap[0];
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
    return min_value;
}

void sort_and_pop_all(const int *values, int count) {
    if (count <= 0) {
        return;
    }
    int *heap = (int *)malloc(count * sizeof(int));
    if (!heap) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    int size = 0;
    for (int i = 0; i < count; i++) {
        push(heap, &size, values[i]);
    }
    while (size > 0) {
        int val = pop(heap, &size);
        printf("%d\n", val);
    }
    free(heap);
}

int main(void) {
    int values[] = {9, 4, 7, 1, 3, 8, 2, 5, 6};
    int count = sizeof(values) / sizeof(values[0]);
    sort_and_pop_all(values, count);
    return 0;
}