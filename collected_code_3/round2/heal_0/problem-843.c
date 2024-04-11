#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100000

typedef struct Heap {
    int size;
    int data[MAX_HEAP_SIZE];
} Heap;

Heap* createHeap() {
    Heap* h = (Heap*)malloc(sizeof(Heap));
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
        printf("\nOverflow");
        return;
    }

    h->data[h->size++] = val;
    int i = h->size - 1;

    while (i != 0 && h->data[(i - 1) / 2] > h->data[i]) {
        swap(&h->data[i], &h->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int deleteHeap(Heap* h) {
    if (h->size <= 0)
        return -1;
    if (h->size == 1) {
        h->size--;
        return h->data[0];
    }

    int root = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;
    heapify(h, 0);

    return root;
}

int nthSuperUglyNumber(int n, int* primes, int primesSize) {
    Heap* h = createHeap();
    insertHeap(h, 1);
    int count = 0;
    int val = 0;

    while (count < n) {
        val = deleteHeap(h);
        while (h->size > 0 && h->data[0] == val)
            val = deleteHeap(h);
        count++;

        for (int i = 0; i < primesSize; i++)
            insertHeap(h, val * primes[i]);
    }

    return val;
}

int main() {
    int primes[] = {2, 7, 13, 19};
    int n = 12;
    int primesSize = sizeof(primes) / sizeof(primes[0]);

    printf("The %dth super ugly number is %d", n, nthSuperUglyNumber(n, primes, primesSize));

    return 0;
}