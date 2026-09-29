#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100000

typedef struct Heap {
    int size;
    int data[MAX_HEAP_SIZE];
} Heap;

Heap* createHeap() {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    if (!h)
        return NULL;
    h->size = 0;
    return h;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap* h, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < h->size && h->data[left] < h->data[smallest])
        smallest = left;

    if (right < h->size && h->data[right] < h->data[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&h->data[i], &h->data[smallest]);
        heapify(h, smallest);
    }
}

void insertHeap(Heap* h, int val) {
    if (h->size == MAX_HEAP_SIZE) {
        printf("\nHeap is full\n");
        return;
    }

    h->data[h->size] = val;
    h->size++;

    for (int i = h->size / 2 - 1; i >= 0; i--)
        heapify(h, i);
}

int deleteRoot(Heap* h) {
    int root = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;
    heapify(h, 0);

    return root;
}

int nthSuperUglyNumber(int n, int primes[], int k) {
    Heap* h = createHeap();
    if (!h)
        return -1;
    insertHeap(h, 1);

    int uglyNumber;
    for (int i = 0; i < n; i++) {
        uglyNumber = deleteRoot(h);

        for (int j = 0; j < k; j++) {
            int nextUglyNumber = uglyNumber * primes[j];
            insertHeap(h, nextUglyNumber);
        }
    }

    free(h);
    return uglyNumber;
}

int main() {
    int primes[] = {2, 7, 13, 19};
    int n = 12;
    int k = sizeof(primes) / sizeof(primes[0]);

    printf("The %dth super ugly number is %d\n", n, nthSuperUglyNumber(n, primes, k));

    return 0;
}