#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    size_t size;
    size_t capacity;
} Heap;

Heap *create_heap(size_t capacity) {
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->arr = (int *)malloc(capacity * sizeof(int));
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void free_heap(Heap *h) {
    free(h->arr);
    free(h);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap *h, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < h->size && h->arr[left] < h->arr[smallest])
        smallest = left;
    if (right < h->size && h->arr[right] < h->arr[smallest])
        smallest = right;
    
    if (smallest != i) {
        swap(&h->arr[i], &h->arr[smallest]);
        heapify(h, smallest);
    }
}

void build_heap(Heap *h) {
    for (int i = (h->size / 2) - 1; i >= 0; i--) {
        heapify(h, i);
    }
}

int pop(Heap *h) {
    if (h->size <= 0) return -1;
    int root = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    heapify(h, 0);
    return root;
}

void push(Heap *h, int value) {
    if (h->size == h->capacity) return;
    int i = h->size++;
    while (i > 0 && h->arr[(i - 1) / 2] > h->arr[i]) {
        swap(&h->arr[i], &h->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void heap_sort(int *arr, size_t n) {
    Heap *h = create_heap(n);

    for (size_t i = 0; i < n; i++) {
        push(h, arr[i]);
    }

    for (size_t i = 0; i < n; i++) {
        arr[i] = pop(h);
    }

    free_heap(h);
}

int main() {
    int arr[] = {34, 12, 89, 56, 23, 5, 78, 9};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    heap_sort(arr, n);

    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}