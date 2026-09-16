#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_HEAP_SIZE 100

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} MinHeap;

bool min_heap_init(MinHeap *heap, size_t capacity) {
    if (heap == NULL || capacity == 0) {
        return false;
    }
    
    heap->data = malloc(capacity * sizeof(int));
    if (heap->data == NULL) {
        return false;
    }
    
    heap->size = 0;
    heap->capacity = capacity;
    return true;
}

void min_heap_free(MinHeap *heap) {
    if (heap != NULL) {
        free(heap->data);
        heap->data = NULL;
        heap->size = 0;
        heap->capacity = 0;
    }
}

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void sift_down(MinHeap *heap, size_t index) {
    size_t smallest = index;
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;
    
    if (left < heap->size && heap->data[left] < heap->data[smallest]) {
        smallest = left;
    }
    
    if (right < heap->size && heap->data[right] < heap->data[smallest]) {
        smallest = right;
    }
    
    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        sift_down(heap, smallest);
    }
}

static void sift_up(MinHeap *heap, size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap->data[parent] <= heap->data[index]) {
            break;
        }
        swap(&heap->data[parent], &heap->data[index]);
        index = parent;
    }
}

bool min_heap_replace_min(MinHeap *heap, int new_item, int *old_min) {
    if (heap == NULL || heap->size == 0) {
        return false;
    }
    
    if (old_min != NULL) {
        *old_min = heap->data[0];
    }
    
    heap->data[0] = new_item;
    sift_down(heap, 0);
    
    return true;
}

bool min_heap_insert(MinHeap *heap, int value) {
    if (heap == NULL || heap->size >= heap->capacity) {
        return false;
    }
    
    heap->data[heap->size] = value;
    sift_up(heap, heap->size);
    heap->size++;
    
    return true;
}

static void print_heap(const MinHeap *heap) {
    if (heap == NULL || heap->size == 0) {
        printf("Heap is empty\n");
        return;
    }
    
    printf("Heap: ");
    for (size_t i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

int main(void) {
    MinHeap heap;
    int values[] = {10, 20, 15, 40, 50, 100, 25, 45};
    size_t num_values = sizeof(values) / sizeof(values[0]);
    int removed_min;
    int new_item = 5;
    
    if (!min_heap_init(&heap, MAX_HEAP_SIZE)) {
        fprintf(stderr, "Failed to initialize heap\n");
        return EXIT_FAILURE;
    }
    
    for (size_t i = 0; i < num_values; i++) {
        if (!min_heap_insert(&heap, values[i])) {
            fprintf(stderr, "Failed to insert value %d\n", values[i]);
            min_heap_free(&heap);
            return EXIT_FAILURE;
        }
    }
    
    printf("Original ");
    print_heap(&heap);
    
    if (min_heap_replace_min(&heap, new_item, &removed_min)) {
        printf("Removed minimum: %d\n", removed_min);
        printf("Inserted: %d\n", new_item);
        printf("After operation ");
        print_heap(&heap);
    } else {
        fprintf(stderr, "Failed to replace minimum element\n");
        min_heap_free(&heap);
        return EXIT_FAILURE;
    }
    
    min_heap_free(&heap);
    return EXIT_SUCCESS;
}