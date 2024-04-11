#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *heapArr;
    int last;
    int capacity;
} Heap;

Heap* createHeap(int capacity) {
    Heap* h = (Heap*) malloc(sizeof(Heap));
    
    if(h == NULL)
        return NULL;

    h->heapArr = (int*) malloc(sizeof(int) * capacity);

    if(h->heapArr == NULL) {
        free(h);
        return NULL;
    }
    
    h->last = -1;
    h->capacity = capacity;
    return h;
}

void insertHeap(Heap* h, int value) {
    if(h->last == h->capacity - 1) {
        return;
    }

    h->heapArr[++h->last] = value;
    int child = h->last;
    int parent = (child - 1) / 2;
    
    while(child > 0 && h->heapArr[child] < h->heapArr[parent]) {
        int temp = h->heapArr[child];
        h->heapArr[child] = h->heapArr[parent];
        h->heapArr[parent] = temp;
        child = parent;
        parent = (child - 1) / 2;
    }
}

int deleteHeap(Heap* h) {
    if(h->last == -1) {
        return -1;
    }

    int min = h->heapArr[0];
    h->heapArr[0] = h->heapArr[h->last--];
    int parent = 0;
    
    while(1) {
        int leftChild = 2 * parent + 1;
        int rightChild = 2 * parent + 2;
        int smallest = parent;
        
        if(leftChild <= h->last && h->heapArr[leftChild] < h->heapArr[smallest]) {
            smallest = leftChild;
        }
        
        if(rightChild <= h->last && h->heapArr[rightChild] < h->heapArr[smallest]) {
            smallest = rightChild;
        }
        
        if(smallest != parent) {
            int temp = h->heapArr[parent];
            h->heapArr[parent] = h->heapArr[smallest];
            h->heapArr[smallest] = temp;
            parent = smallest;
        } else {
            break;
        }
    }
    return min;
}

void findNCheapItems(int* arr, int n, int size) {
    Heap* h = createHeap(n);
    
    if(h == NULL)
        return;

    for(int i = 0; i < n; i++) {
        insertHeap(h, arr[i]);
    }
    
    for(int i = n; i < size; i++) {
        if(arr[i] < h->heapArr[0]) {
            h->heapArr[0] = arr[i];
            deleteHeap(h);
            insertHeap(h, arr[i]);
        }
    }
    
    printf("The %d cheapest items are: ", n);
    
    for(int i = 0; i < n; i++) {
        printf("%d ", deleteHeap(h));
    }
    
    printf("\n");
    free(h->heapArr);
    free(h);
}

int main() {
    int arr[] = {20, 12, 35, 15, 10, 80, 30, 17, 2, 1};
    int n = 5;
    int size = sizeof(arr) / sizeof(arr[0]);
    findNCheapItems(arr, n, size);
    return 0;
}