#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

typedef struct {
    int data[MAX_HEAP_SIZE];
    int size;
} Heap;

void initHeap(Heap *heap) {
    heap->size = 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(Heap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->data[index] < heap->data[parent]) {
            swap(&heap->data[index], &heap->data[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapifyDown(Heap *heap, int index) {
    while (index < heap->size) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }

        if (smallest != index) {
            swap(&heap->data[index], &heap->data[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

int insertHeap(Heap *heap, int value) {
    if (heap->size >= MAX_HEAP_SIZE) {
        return -1;
    }

    heap->data[heap->size] = value;
    heap->size++;
    heapifyUp(heap, heap->size - 1);
    return 0;
}

int deleteMinHeap(Heap *heap, int *deletedValue) {
    if (heap->size <= 0) {
        return -1;
    }

    *deletedValue = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    
    if (heap->size > 0) {
        heapifyDown(heap, 0);
    }
    
    return 0;
}

int replaceMinWithNewValue(Heap *heap, int newValue, int *oldMinValue) {
    if (deleteMinHeap(heap, oldMinValue) != 0) {
        return -1;
    }
    
    if (insertHeap(heap, newValue) != 0) {
        return -1;
    }
    
    return 0;
}

void printHeap(Heap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

int main(void) {
    Heap heap;
    initHeap(&heap);
    
    int values[] = {5, 3, 8, 1, 9, 6, 7, 2, 4};
    int numValues = sizeof(values) / sizeof(values[0]);
    
    for (int i = 0; i < numValues; i++) {
        if (insertHeap(&heap, values[i]) != 0) {
            printf("Failed to insert value %d\n", values[i]);
            return EXIT_FAILURE;
        }
    }
    
    printf("Original heap: ");
    printHeap(&heap);
    
    int oldMin;
    int newValue = 10;
    
    if (replaceMinWithNewValue(&heap, newValue, &oldMin) != 0) {
        printf("Failed to replace minimum value\n");
        return EXIT_FAILURE;
    }
    
    printf("Deleted minimum value: %d\n", oldMin);
    printf("Inserted new value: %d\n", newValue);
    printf("Updated heap: ");
    printHeap(&heap);
    
    return EXIT_SUCCESS;
}