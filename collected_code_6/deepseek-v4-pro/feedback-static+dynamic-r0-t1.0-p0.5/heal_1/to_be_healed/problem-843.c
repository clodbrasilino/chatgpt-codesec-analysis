#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long value;
    int prime;
    int index;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

/* Possible weaknesses found:
 *  expected 'HeapNode *' but argument is of type 'HeapNode'
 *  passing argument to parameter 'b' here
 */
void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyDown(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    
    if (left < heap->size && heap->data[left].value < heap->data[smallest].value)
        smallest = left;
    if (right < heap->size && heap->data[right].value < heap->data[smallest].value)
        smallest = right;
    
    if (smallest != idx) {
        swap(&heap->data[idx], &heap->data[smallest]);
        heapifyDown(heap, smallest);
    }
}

void heapifyUp(MinHeap *heap, int idx) {
    int parent = (idx - 1) / 2;
    while (idx > 0 && heap->data[parent].value > heap->data[idx].value) {
        /* Possible weaknesses found:
         *  incompatible type for argument 2 of 'swap'
         *  passing 'HeapNode' to parameter of incompatible type 'HeapNode *'; take the address with &
         */
        swap(&heap->data[parent], heap->data[idx]);
        idx = parent;
        parent = (idx - 1) / 2;
    }
}

void heapPush(MinHeap *heap, HeapNode node) {
    if (heap->size >= heap->capacity) {
        heap->capacity *= 2;
        heap->data = (HeapNode*)realloc(heap->data, sizeof(HeapNode) * heap->capacity);
    }
    heap->data[heap->size] = node;
    heapifyUp(heap, heap->size);
    heap->size++;
}

HeapNode heapPop(MinHeap *heap) {
    HeapNode top = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return top;
}

void freeHeap(MinHeap *heap) {
    free(heap->data);
    free(heap);
}

/* Possible weaknesses found:
 *  Parameter 'primes' can be declared as pointer to const [constParameterPointer]
 */
int nthSuperUglyNumber(int n, int* primes, int primesSize) {
    if (n <= 0 || primesSize <= 0) return 0;
    if (n == 1) return 1;
    
    long *ugly = (long*)malloc(sizeof(long) * n);
    ugly[0] = 1;
    
    MinHeap *heap = createHeap(primesSize);
    
    for (int i = 0; i < primesSize; i++) {
        HeapNode node;
        node.value = primes[i];
        node.prime = primes[i];
        node.index = 0;
        heapPush(heap, node);
    }
    
    for (int i = 1; i < n; i++) {
        HeapNode node = heapPop(heap);
        ugly[i] = node.value;
        
        node.index++;
        node.value = (long)node.prime * ugly[node.index];
        heapPush(heap, node);
        
        while (heap->size > 0 && heap->data[0].value == ugly[i]) {
            HeapNode dup = heapPop(heap);
            dup.index++;
            dup.value = (long)dup.prime * ugly[dup.index];
            heapPush(heap, dup);
        }
    }
    
    int result = (int)ugly[n - 1];
    free(ugly);
    freeHeap(heap);
    return result;
}

int main() {
    int primes1[] = {2, 7, 13, 19};
    int n1 = 12;
    int size1 = sizeof(primes1) / sizeof(primes1[0]);
    printf("Test 1: %d\n", nthSuperUglyNumber(n1, primes1, size1));
    
    int primes2[] = {2, 3, 5};
    int n2 = 10;
    int size2 = sizeof(primes2) / sizeof(primes2[0]);
    printf("Test 2: %d\n", nthSuperUglyNumber(n2, primes2, size2));
    
    int primes3[] = {3, 5, 7, 11, 13};
    int n3 = 20;
    int size3 = sizeof(primes3) / sizeof(primes3[0]);
    printf("Test 3: %d\n", nthSuperUglyNumber(n3, primes3, size3));
    
    return 0;
}