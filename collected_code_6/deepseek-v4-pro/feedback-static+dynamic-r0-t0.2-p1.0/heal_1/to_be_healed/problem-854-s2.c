#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Heap;

static void heap_swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void heap_sift_down(Heap *heap, size_t index) {
    size_t largest = index;
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;

    if (left < heap->size && heap->data[left] > heap->data[largest]) {
        largest = left;
    }
    if (right < heap->size && heap->data[right] > heap->data[largest]) {
        largest = right;
    }
    if (largest != index) {
        heap_swap(&heap->data[index], &heap->data[largest]);
        heap_sift_down(heap, largest);
    }
}

static void heap_sift_up(Heap *heap, size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap->data[index] > heap->data[parent]) {
            heap_swap(&heap->data[index], &heap->data[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

int heap_init(Heap *heap, size_t capacity) {
    if (heap == NULL || capacity == 0) {
        return -1;
    }
    heap->data = (int *)malloc(capacity * sizeof(int));
    if (heap->data == NULL) {
        return -1;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return 0;
}

void heap_destroy(Heap *heap) {
    if (heap != NULL && heap->data != NULL) {
        free(heap->data);
        heap->data = NULL;
        heap->size = 0;
        heap->capacity = 0;
    }
}

int heap_push(Heap *heap, int value) {
    if (heap == NULL || heap->data == NULL) {
        return -1;
    }
    if (heap->size >= heap->capacity) {
        size_t new_capacity = heap->capacity * 2;
        int *new_data = (int *)realloc(heap->data, new_capacity * sizeof(int));
        if (new_data == NULL) {
            return -1;
        }
        heap->data = new_data;
        heap->capacity = new_capacity;
    }
    heap->data[heap->size] = value;
    heap_sift_up(heap, heap->size);
    heap->size++;
    return 0;
}

int heap_pop(Heap *heap, int *value) {
    if (heap == NULL || heap->data == NULL || heap->size == 0 || value == NULL) {
        return -1;
    }
    *value = heap->data[0];
    heap->size--;
    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        heap_sift_down(heap, 0);
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int heap_build_from_array(Heap *heap, int *array, size_t length) {
    if (heap == NULL || array == NULL || length == 0) {
        return -1;
    }
    if (heap_init(heap, length) != 0) {
        return -1;
    }
    for (size_t i = 0; i < length; i++) {
        heap->data[i] = array[i];
    }
    heap->size = length;
    for (size_t i = length / 2; i > 0; i--) {
        heap_sift_down(heap, i - 1);
    }
    return 0;
}

int heap_peek(const Heap *heap, int *value) {
    if (heap == NULL || heap->data == NULL || heap->size == 0 || value == NULL) {
        return -1;
    }
    *value = heap->data[0];
    return 0;
}

size_t heap_size(const Heap *heap) {
    if (heap == NULL) {
        return 0;
    }
    return heap->size;
}

int main(void) {
    int array[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    size_t length = sizeof(array) / sizeof(array[0]);
    Heap heap;
    int value;

    if (heap_build_from_array(&heap, array, length) != 0) {
        fprintf(stderr, "Failed to build heap\n");
        return EXIT_FAILURE;
    }

    printf("Heap size: %zu\n", heap_size(&heap));

    if (heap_peek(&heap, &value) == 0) {
        printf("Top element: %d\n", value);
    }

    printf("Heap elements in descending order:\n");
    while (heap_pop(&heap, &value) == 0) {
        printf("%d ", value);
    }
    printf("\n");

    heap_destroy(&heap);

    if (heap_init(&heap, 4) != 0) {
        fprintf(stderr, "Failed to initialize heap\n");
        return EXIT_FAILURE;
    }

    heap_push(&heap, 10);
    heap_push(&heap, 20);
    heap_push(&heap, 5);
    heap_push(&heap, 30);
    heap_push(&heap, 15);

    printf("Dynamic heap size: %zu\n", heap_size(&heap));

    while (heap_pop(&heap, &value) == 0) {
        printf("%d ", value);
    }
    printf("\n");

    heap_destroy(&heap);

    return EXIT_SUCCESS;
}