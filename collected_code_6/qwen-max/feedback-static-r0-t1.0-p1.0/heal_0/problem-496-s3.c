#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    size_t used_size;
    size_t capacity;
} Heap;

void heapify(Heap *h, size_t i) {
    size_t smallest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < h->used_size && h->array[left] < h->array[smallest])
        smallest = left;

    if (right < h->used_size && h->array[right] < h->array[smallest])
        smallest = right;

    if (smallest != i) {
        int temp = h->array[i];
        h->array[i] = h->array[smallest];
        h->array[smallest] = temp;
        heapify(h, smallest);
    }
}

void build_heap(Heap *h) {
    for (size_t i = (h->used_size / 2) - 1; i > 0; i--) {
        heapify(h, i);
    }
}

void insert(Heap *h, int value) {
    if (h->used_size >= h->capacity) {
        h->capacity *= 2;
        h->array = (int*)realloc(h->array, h->capacity * sizeof(int));
    }

    h->array[h->used_size++] = value;
    int i = h->used_size - 1;
    while (i != 0 && h->array[(i - 1) / 2] > h->array[i]) {
        int temp = h->array[i];
        h->array[i] = h->array[(i - 1) / 2];
        h->array[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

int extract_min(Heap *h) {
    if (h->used_size == 0) return -1;
    if (h->used_size == 1) {
        int root = h->array[0];
        h->used_size--;
        return root;
    }

    int root = h->array[0];
    h->array[0] = h->array[h->used_size - 1];
    h->used_size--;

    heapify(h, 0);

    return root;
}

Heap* create_heap() {
    Heap *h = (Heap*)malloc(sizeof(Heap));
    h->array = (int*)malloc(10 * sizeof(int));
    h->capacity = 10;
    h->used_size = 0;
    return h;
}

void delete_heap(Heap *h) {
    free(h->array);
    free(h);
}

int main() {
    int numbers[] = {34, 19, 27, 18, 15, 31, 12, 5, 20};
    size_t n = sizeof(numbers) / sizeof(numbers[0]);

    Heap *h = create_heap();
    for (size_t i = 0; i < n; ++i) {
        insert(h, numbers[i]);
    }

    for (size_t i = 0; i < n; ++i) {
        printf("%d ", extract_min(h));
    }

    delete_heap(h);
    return 0;
}