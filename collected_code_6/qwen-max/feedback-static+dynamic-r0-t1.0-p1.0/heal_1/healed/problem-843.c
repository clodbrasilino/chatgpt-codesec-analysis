#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *heap;
    int size;
    int capacity;
} minHeap;

int parent(int i) { return (i - 1) / 2; }
int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(minHeap *h, int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < h->size && h->heap[l] < h->heap[i])
        smallest = l;
    if (r < h->size && h->heap[r] < h->heap[smallest])
        smallest = r;
    if (smallest != i) {
        swap(&h->heap[i], &h->heap[smallest]);
        minHeapify(h, smallest);
    }
}

void decreaseKey(minHeap *h, int i, int new_val) {
    h->heap[i] = new_val;
    while (i != 0 && h->heap[parent(i)] > h->heap[i]) {
        swap(&h->heap[i], &h->heap[parent(i)]);
        i = parent(i);
    }
}

void minHeapInsert(minHeap *h, int k) {
    h->size++;
    h->heap[h->size - 1] = INT_MAX;
    decreaseKey(h, h->size - 1, k);
}

int extractMin(minHeap *h) {
    if (h->size == 1) {
        h->size--;
        return h->heap[0];
    }
    int root = h->heap[0];
    h->heap[0] = h->heap[h->size - 1];
    h->size--;
    minHeapify(h, 0);
    return root;
}

minHeap *newMinHeap(int capacity) {
    minHeap *h = (minHeap *)malloc(sizeof(minHeap));
    h->heap = (int *)malloc(capacity * sizeof(int));
    h->capacity = capacity;
    h->size = 0;
    return h;
}

int nthSuperUglyNumber(int n, const int* primes, int k) {
    minHeap *h = newMinHeap(k * n + 1);
    int ugly[n];
    ugly[0] = 1;
    for (int i = 1; i < n; i++) {
        int next_ugly_no = INT_MAX;
        for (int j = 0; j < k; j++) {
            minHeapInsert(h, ugly[i - 1] * primes[j]);
            next_ugly_no = extractMin(h);
        }
        ugly[i] = next_ugly_no;
    }
    free(h->heap);
    free(h);
    return ugly[n - 1];
}

int main() {
    int primes[] = {2, 3, 5};
    int k = 3;
    int n = 12;
    printf("The %dth super ugly number is %d\n", n, nthSuperUglyNumber(n, primes, k));
    return 0;
}