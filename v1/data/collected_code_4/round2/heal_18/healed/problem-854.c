#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* arr;
    size_t used;
    size_t size;
} Array;

void create(Array* array, size_t initialSize) {
    array->arr = (int*)calloc(initialSize, sizeof(int));
    if(!array->arr) {
        exit(EXIT_FAILURE);
    }
    array->size = initialSize;
    array->used = 0;
}

void insert(Array* array, int element) {
    if (array->used == array->size) {
        size_t newSize = array->size * 2;
        int* temp = realloc(array->arr, newSize * sizeof(int));
        if (!temp) {
            free(array->arr);
            array->arr = NULL;
            array->used = array->size = 0;
            return;
        }  
        array->arr = temp;
        array->size = newSize;
    }  
    array->arr[array->used++] = element;
}

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void heapify(Array* array, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && array->arr[left] > array->arr[largest])
        largest = left;

    if(right < n && array->arr[right] > array->arr[largest])
        largest = right;

    if(largest != i) {
        swap(&array->arr[i], &array->arr[largest]);
        heapify(array, n, largest);
    }
}

void heapSort(Array* array) {
    int n = array->used;
    for(int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    for(int i = n - 1; i >= 0; i--) {
        swap(&array->arr[0], &array->arr[i]);
        array->used--;
        heapify(array, i, 0);
    }
    array->used = n;
}

void print(Array* array) {
    for(size_t i = 0; i < array->used; i++)
        printf("%d ", array->arr[i]);
    printf("\n");
}

void destroy(Array* array) {
    free(array->arr);
    array->arr = NULL;
    array->size = array->used = 0;
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