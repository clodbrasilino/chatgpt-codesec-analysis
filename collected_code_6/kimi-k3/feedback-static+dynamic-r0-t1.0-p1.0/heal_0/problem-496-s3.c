#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Heap;

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_up(Heap *heap, size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap->data[parent] >= heap->data[index]) {
            break;
        }
        swap(&heap->data[parent], &heap->data[index]);
        index = parent;
    }
}

static void heapify_down(Heap *heap, size_t index) {
    while (1) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t largest = index;

        if (left < heap->size && heap->data[left] > heap->data[largest]) {
            largest = left;
        }
        if (right < heap->size && heap->data[right] > heap->data[largest]) {
            largest = right;
        }
        if (largest == index) {
            break;
        }
        swap(&heap->data[index], &heap->data[largest]);
        index = largest;
    }
}

static int heap_init(Heap *heap, size_t capacity) {
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

static void heap_free(Heap *heap) {
    if (heap != NULL && heap->data != NULL) {
        free(heap->data);
        heap->data = NULL;
        heap->size = 0;
        heap->capacity = 0;
    }
}

static int heap_insert(Heap *heap, int value) {
    if (heap == NULL || heap->data == NULL) {
        return -1;
    }
    if (heap->size < heap->capacity) {
        heap->data[heap->size] = value;
        heapify_up(heap, heap->size);
        heap->size++;
    } else if (value < heap->data[0]) {
        heap->data[0] = value;
        heapify_down(heap, 0);
    }
    return 0;
}

static int heap_extract_max(Heap *heap, int *result) {
    if (heap == NULL || heap->data == NULL || result == NULL || heap->size == 0) {
        return -1;
    }
    *result = heap->data[0];
    heap->size--;
    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        heapify_down(heap, 0);
    }
    return 0;
}

int find_smallest(const int *numbers, size_t count, size_t k, int *result) {
    if (numbers == NULL || result == NULL || k == 0 || k > count) {
        return -1;
    }

    Heap heap;
    if (heap_init(&heap, k) != 0) {
        return -1;
    }

    for (size_t i = 0; i < count; i++) {
        if (heap_insert(&heap, numbers[i]) != 0) {
            heap_free(&heap);
            return -1;
        }
    }

    for (size_t i = 0; i < k; i++) {
        if (heap_extract_max(&heap, &result[k - 1 - i]) != 0) {
            heap_free(&heap);
            return -1;
        }
    }

    heap_free(&heap);
    return 0;
}

int main(void) {
    int numbers[] = {7, 10, 4, 3, 20, 15, 8, 1};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    size_t k = 3;
    int *smallest = (int *)malloc(k * sizeof(int));

    if (smallest == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (find_smallest(numbers, count, k, smallest) != 0) {
        fprintf(stderr, "Failed to find smallest elements\n");
        free(smallest);
        return EXIT_FAILURE;
    }

    printf("The %zu smallest integers are: ", k);
    for (size_t i = 0; i < k; i++) {
        printf("%d ", smallest[i]);
    }
    printf("\n");

    free(smallest);
    return EXIT_SUCCESS;
}