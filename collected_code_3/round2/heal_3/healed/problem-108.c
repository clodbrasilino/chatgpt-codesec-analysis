#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* arr;
    int size;
    int index;
} Iterator;

typedef struct {
    Iterator** arr;
    int size;
} Heap;

Iterator* createIterator(int* arr, int size) {
    Iterator* it = (Iterator*)malloc(sizeof(Iterator));

    if (it == NULL)
        return NULL;

    it->arr = arr;
    it->size = size;
    it->index = 0;

    return it;
}

Heap* createHeap(int size) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));

    if (heap == NULL)
        return NULL;

    heap->arr = (Iterator**)malloc(sizeof(Iterator*) * size);

    if (heap->arr == NULL) {
        free(heap);
        return NULL;
    }

    heap->size = 0;

    return heap;
}

void swap(Iterator** a, Iterator** b) {
    Iterator* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap* heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->arr[left]->arr[heap->arr[left]->index] < heap->arr[smallest]->arr[heap->arr[smallest]->index])
        smallest = left;

    if (right < heap->size && heap->arr[right]->arr[heap->arr[right]->index] < heap->arr[smallest]->arr[heap->arr[smallest]->index])
        smallest = right;

    if (smallest != i) {
        swap(&heap->arr[i], &heap->arr[smallest]);
        heapify(heap, smallest);
    }
}

int insertHeap(Heap* heap, Iterator* it) {
    if (heap == NULL || it == NULL)
        return -1;

    int i = heap->size;
    heap->arr[i] = it;

    while (i != 0 && heap->arr[(i - 1) / 2]->arr[heap->arr[(i - 1) / 2]->index] > heap->arr[i]->arr[heap->arr[i]->index]) {
        swap(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

    heap->size++;

    return 0;
}

Iterator* extractMin(Heap* heap) {
    if (heap == NULL || heap->size <= 0)
        return NULL;

    Iterator* root = heap->arr[0];

    if (heap->size > 1) {
        heap->arr[0] = heap->arr[heap->size - 1];
        heapify(heap, 0);
    }

    heap->size--;

    return root;
}

void mergeSortedArrays(int* arr, int size, int** input, int* lengths, int n) {
    Heap* heap = createHeap(n);

    if (heap == NULL)
        return;

    for (int i = 0; i < n; i++)
        if (insertHeap(heap, createIterator(input[i], lengths[i])) != 0)
            return;

    int index = 0;

    while (heap && heap->size > 0) {
        Iterator* it = extractMin(heap);
        if (it) {
            arr[index++] = it->arr[it->index];

            if (it->index < it->size - 1) {
                it->index++;
                insertHeap(heap, it);
            } else {
                free(it);
            }
        }
    }

    free(heap->arr);
    free(heap);
}

int main() {
    int arr1[] = {1, 5, 9};
    int arr2[] = {2, 6, 10};
    int arr3[] = {3, 7, 11};
    int arr4[] = {4, 8, 12};

    int* input[] = {arr1, arr2, arr3, arr4};
    int lengths[] = {3, 3, 3, 3};

    int size = 12;
    int* arr = (int*)malloc(sizeof(int) * size);

    if (arr == NULL)
        return 1;

    mergeSortedArrays(arr, size, input, lengths, 4);

    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);

    free(arr);
    return 0;
}