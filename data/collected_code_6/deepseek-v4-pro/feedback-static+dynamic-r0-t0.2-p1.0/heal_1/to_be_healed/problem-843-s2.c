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
        swap(&heap->data[parent], &heap->data[idx]);
        idx = parent;
        parent = (idx - 1) / 2;
    }
}

void heapPush(MinHeap *heap, long value, int prime, int index) {
    if (heap->size >= heap->capacity) {
        heap->capacity *= 2;
        heap->data = (HeapNode*)realloc(heap->data, sizeof(HeapNode) * heap->capacity);
    }
    heap->data[heap->size].value = value;
    heap->data[heap->size].prime = prime;
    heap->data[heap->size].index = index;
    heap->size++;
    heapifyUp(heap, heap->size - 1);
}

HeapNode heapPop(MinHeap *heap) {
    HeapNode min = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return min;
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
        heapPush(heap, (long)primes[i], primes[i], 0);
    }
    
    for (int i = 1; i < n; i++) {
        HeapNode node = heapPop(heap);
        ugly[i] = node.value;
        
        heapPush(heap, (long)node.prime * ugly[node.index + 1], node.prime, node.index + 1);
        
        while (heap->size > 0 && heap->data[0].value == ugly[i]) {
            HeapNode dup = heapPop(heap);
            heapPush(heap, (long)dup.prime * ugly[dup.index + 1], dup.prime, dup.index + 1);
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
    printf("12th super ugly number: %d\n", nthSuperUglyNumber(n1, primes1, size1));
    
    int primes2[] = {2, 3, 5};
    int n2 = 10;
    int size2 = sizeof(primes2) / sizeof(primes2[0]);
    printf("10th super ugly number: %d\n", nthSuperUglyNumber(n2, primes2, size2));
    
    int primes3[] = {3, 5, 7, 11, 13};
    int n3 = 20;
    int size3 = sizeof(primes3) / sizeof(primes3[0]);
    printf("20th super ugly number: %d\n", nthSuperUglyNumber(n3, primes3, size3));
    
    return 0;
}