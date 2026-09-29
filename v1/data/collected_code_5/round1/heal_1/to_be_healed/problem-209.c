#include<stdio.h>
#include<stdlib.h>

typedef struct Heap {
    int *array;
    int count;
    int capacity;
}Heap;

Heap* CreateHeap(int capacity) {
    Heap *h = (Heap*) malloc(sizeof(Heap));
    if(h == NULL) {
        printf("Memory Error.");
        return NULL;
    }
    h->count=0;
    h->capacity = capacity;
    h->array = (int*) malloc(sizeof(int) * h->capacity);
    if(h->array == NULL) {
        /* Possible weaknesses found:
         *  Potential leak of memory pointed to by 'h' [unix.Malloc]
         */
        printf("Memory Error.");
        return NULL;
    }
    return h;
}

void insert(Heap *h, int key) {
    if(h->count < h->capacity) {
        h->array[h->count++] = key;
    }
}

void heapify(Heap *h, int i) {
    int min, temp;
    int left = 2*i + 1;
    int right = 2*i + 2;
    if(left < h->count && h->array[left] < h->array[i])
        min = left;
    else
        min = i;
    if(right < h->count && h->array[right] < h->array[min])
        min = right;
    if(min != i) {
        temp = h->array[i];
        h->array[i] = h->array[min];
        h->array[min] = temp;
        heapify(h, min);
    }
}

void deleteMin(Heap *h) {
    if(h->count == 0){
        printf("Heap is Empty.\n");
        return;
    }
    /* Possible weaknesses found:
     *  Value stored to 'min' during its initialization is never read [deadcode.DeadStores]
     */
    int min = h->array[0];
    h->array[0] = h->array[h->count - 1];
    h->count--;
    heapify(h, 0);
}

int main() {
    Heap *heap = CreateHeap(20);
    if(heap == NULL)
        return 1;
    insert(heap, 5);
    insert(heap, 8);
    insert(heap, 2);
    insert(heap, 9);
    deleteMin(heap);
    insert(heap, 1);
    /* Possible weaknesses found:
     *  Potential leak of memory pointed to by 'heap' [unix.Malloc]
     */
    return 0;
}