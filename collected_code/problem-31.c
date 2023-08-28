#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int value;
    int count;
} Element;

typedef struct {
    Element *arr;
    int size;
    int capacity;
} Heap;

Heap* createHeap(int capacity) {
    Heap* heap = (Heap*) malloc(sizeof(Heap));
    heap->arr = (Element*) malloc(capacity * sizeof(Element));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(Element *a, Element *b) {
    Element temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap *heap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->arr[left].count > heap->arr[largest].count)
        largest = left;

    if (right < heap->size && heap->arr[right].count > heap->arr[largest].count)
        largest = right;

    if (largest != index) {
        swap(&heap->arr[index], &heap->arr[largest]);
        heapify(heap, largest);
    }
}

Heap* buildHeap(Element *arr, int size) {
    Heap* heap = createHeap(size);
    heap->size = size;

    for (int i = (size - 2) / 2; i >= 0; --i) {
        heapify(heap, i);
    }

    return heap;
}

void insertHeap(Heap *heap, Element element) {
    if (heap->size < heap->capacity) {
        ++(heap->size);
        int i = heap->size - 1;

        while (i && element.count > heap->arr[(i - 1) / 2].count) {
            heap->arr[i] = heap->arr[(i - 1) / 2];
            i = (i - 1) / 2;
        }

        heap->arr[i] = element;
    }
    else if (element.count > heap->arr[0].count) {
        heap->arr[0] = element;
        heapify(heap, 0);
    }
}

void findTopKFrequent(int arr[], int size, int k) {
    Heap* heap = buildHeap(NULL, k);

    for (int i = 0; i < size; ++i) {
        int j;
        for (j = 0; j < heap->size; ++j) {
            if (heap->arr[j].value == arr[i]) {
                ++(heap->arr[j].count);
                break;
            }
        }

        if (j == heap->size) {
            if (heap->size < k) {
                heap->arr[heap->size].value = arr[i];
                heap->arr[heap->size].count = 1;
                ++(heap->size);
            }
            else if (heap->arr[0].count < 1) {
                heap->arr[0].value = arr[i];
                heap->arr[0].count = 1;
                heapify(heap, 0);
            }
        }
    }

    printf("The top %d integers that occur most frequently are:\n", k);
    for (int i = heap->size - 1; i >= 0; --i) {
        printf("%d ", heap->arr[i].value);
    }

    free(heap->arr);
    free(heap);
}

int main() {
    int arr[MAX_SIZE];
    int size, k;

    printf("Enter the size of the array: ");
    scanf("%d", &size);

    printf("Enter the elements of the array in sorted order: ");
    for (int i = 0; i < size; ++i) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the value of k: ");
    scanf("%d", &k);

    findTopKFrequent(arr, size, k);

    return 0;
}