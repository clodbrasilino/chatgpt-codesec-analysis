#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} MinHeap;

MinHeap *heap_create(size_t capacity) {
    MinHeap *h = malloc(sizeof(MinHeap));
    if (!h) return NULL;
    h->data = malloc(capacity * sizeof(int));
    if (!h->data) {
        free(h);
        return NULL;
    }
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void heap_destroy(MinHeap *h) {
    if (h) {
        free(h->data);
        free(h);
    }
}

int heap_push(MinHeap *h, int value) {
    if (!h) return -1;
    if (h->size == h->capacity) {
        size_t new_capacity = h->capacity == 0 ? 1 : h->capacity * 2;
        int *new_data = realloc(h->data, new_capacity * sizeof(int));
        if (!new_data) return -1;
        h->data = new_data;
        h->capacity = new_capacity;
    }
    h->data[h->size] = value;
    size_t i = h->size;
    h->size++;
    while (i > 0) {
        size_t parent = (i - 1) / 2;
        if (h->data[i] < h->data[parent]) {
            int temp = h->data[i];
            h->data[i] = h->data[parent];
            h->data[parent] = temp;
            i = parent;
        } else {
            break;
        }
    }
    return 0;
}

int heap_pop(MinHeap *h, int *value) {
    if (!h || h->size == 0 || !value) return -1;
    *value = h->data[0];
    h->size--;
    if (h->size > 0) {
        h->data[0] = h->data[h->size];
        size_t i = 0;
        while (1) {
            size_t left = 2 * i + 1;
            size_t right = 2 * i + 2;
            size_t smallest = i;
            if (left < h->size && h->data[left] < h->data[smallest]) {
                smallest = left;
            }
            if (right < h->size && h->data[right] < h->data[smallest]) {
                smallest = right;
            }
            if (smallest != i) {
                int temp = h->data[i];
                h->data[i] = h->data[smallest];
                h->data[smallest] = temp;
                i = smallest;
            } else {
                break;
            }
        }
    }
    return 0;
}

int push_all_and_pop_smallest(const int *values, size_t count) {
    MinHeap *h = heap_create(count > 0 ? count : 1);
    if (!h) return -1;
    for (size_t i = 0; i < count; i++) {
        if (heap_push(h, values[i]) != 0) {
            heap_destroy(h);
            return -1;
        }
    }
    int val;
    while (heap_pop(h, &val) == 0) {
        printf("%d\n", val);
    }
    heap_destroy(h);
    return 0;
}

int main(void) {
    int values[] = {42, 15, 8, 23, 4, 16};
    size_t count = sizeof(values) / sizeof(values[0]);
    if (push_all_and_pop_smallest(values, count) != 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}