#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* arr;
    size_t used;
    size_t size;
} Array;

void create(Array* array, size_t initialSize) {
    array->arr = (int*)malloc(initialSize * sizeof(int));
    array->used = 0;
    array->size = initialSize;
}

void insert(Array* array, int element) {
    if (array->used == array->size) {
        array->size *= 2;
        void* newMemory = realloc(array->arr, array->size * sizeof(int));

        if (newMemory == NULL) {
            free(array->arr);
            return;
        }
        array->arr = newMemory;
    }
    array->arr[array->used++] = element;
}

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void heapify(Array* array, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < array->used && array->arr[left] > array->arr[largest])
        largest = left;

    if (right < array->used && array->arr[right] > array->arr[largest])
        largest = right;

    if (largest != i) {
        swap(&array->arr[i], &array->arr[largest]);
        heapify(array, largest);
    }
}

void heapSort(Array* array) {
    for (int i = array->used / 2 - 1; i >= 0; i--)
        heapify(array, i);

    for (int i = array->used - 1; i >= 0; i--) {
        swap(&(array->arr[0]), &(array->arr[i]));
        array->used--;
        heapify(array, 0);
    }
    array->used = array->size;
}

void print(Array* array) {
    for (int i = 0; i < array->used; i++)
        printf("%d ", array->arr[i]);
    printf("\n");
}

void destroy(Array* array) {
    free(array->arr);
    array->arr = NULL;
    array->used = array->size = 0;
}

int main() {
    Array array;
    create(&array, 1);

    insert(&array, 10);
    insert(&array, 15);
    insert(&array, 30);
    insert(&array, 40);

    heapSort(&array);
    print(&array);

    destroy(&array);
    return 0;
}