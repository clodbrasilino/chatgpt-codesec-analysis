#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Heap;

static int heap_init(Heap *heap, size_t capacity) {
    if (heap == NULL || capacity == 0 || capacity > SIZE_MAX / sizeof(int)) {
        return 0;
    }
    heap->data = malloc(capacity * sizeof(int));
    if (heap->data == NULL) {
        return 0;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return 1;
}

static void heap_free(Heap *heap) {
    if (heap == NULL) {
        return;
    }
    free(heap->data);
    heap->data = NULL;
    heap->size = 0;
    heap->capacity = 0;
}

static void swap_int(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static int heap_push(Heap *heap, int value) {
    size_t i;
    size_t parent;

    if (heap == NULL || heap->data == NULL) {
        return 0;
    }

    if (heap->size >= heap->capacity) {
        int *new_data;
        size_t new_capacity;

        if (heap->capacity > SIZE_MAX / 2) {
            return 0;
        }
        new_capacity = heap->capacity * 2;
        if (new_capacity > SIZE_MAX / sizeof(int)) {
            return 0;
        }
        new_data = realloc(heap->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            return 0;
        }
        heap->data = new_data;
        heap->capacity = new_capacity;
    }

    i = heap->size;
    heap->size++;
    heap->data[i] = value;

    while (i > 0) {
        parent = (i - 1) / 2;
        if (heap->data[parent] <= heap->data[i]) {
            break;
        }
        swap_int(&heap->data[parent], &heap->data[i]);
        i = parent;
    }

    return 1;
}

static int heap_pop(Heap *heap, int *value) {
    size_t i;

    if (heap == NULL || heap->data == NULL || heap->size == 0 || value == NULL) {
        return 0;
    }

    *value = heap->data[0];
    heap->size--;

    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        i = 0;

        while (1) {
            size_t left = i * 2 + 1;
            size_t right = i * 2 + 2;
            size_t smallest = i;

            if (left < heap->size && heap->data[left] < heap->data[smallest]) {
                smallest = left;
            }
            if (right < heap->size && heap->data[right] < heap->data[smallest]) {
                smallest = right;
            }
            if (smallest == i) {
                break;
            }
            swap_int(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
    }

    return 1;
}

static int heap_push_all(Heap *heap, const int *values, size_t count) {
    size_t i;

    if (heap == NULL || (values == NULL && count > 0)) {
        return 0;
    }

    for (i = 0; i < count; ++i) {
        if (!heap_push(heap, values[i])) {
            return 0;
        }
    }

    return 1;
}

static int heap_pop_and_print(Heap *heap) {
    if (heap == NULL || heap->data == NULL) {
        return 0;
    }

    while (heap->size > 0) {
        int value;

        if (!heap_pop(heap, &value)) {
            return 0;
        }
        printf("%d\n", value);
    }

    return 1;
}

static int heap_sort(const int *values, size_t count) {
    Heap heap;
    int success;

    if (!heap_init(&heap, count == 0 ? 1 : count)) {
        return 0;
    }

    if (!heap_push_all(&heap, values, count)) {
        heap_free(&heap);
        return 0;
    }

    success = heap_pop_and_print(&heap);
    heap_free(&heap);
    return success;
}

int main(void) {
    int values[] = { 42, -7, 13, 0, 99, 5 };
    size_t count = sizeof(values) / sizeof(values[0]);

    if (!heap_sort(values, count)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}