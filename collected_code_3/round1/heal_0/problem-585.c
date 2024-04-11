#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int count;
    int capacity;
} Heap;

Heap *createHeap(int capacity) {
    Heap *h = (Heap *) malloc(sizeof(Heap));
    h->count = 0;
    h->capacity = capacity;
    h->arr = (int *) malloc(sizeof(int) * h->capacity);
    return h;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap *h, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < h->count && h->arr[left] < h->arr[smallest])
        smallest = left;

    if (right < h->count && h->arr[right] < h->arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&h->arr[i], &h->arr[smallest]);
        heapify(h, smallest);
    }
}

void insert(Heap *h, int value) {
    if (h->count < h->capacity) {
        h->arr[h->count++] = value;
        int i = h->count - 1;

        while (i != 0 && h->arr[(i - 1) / 2] > h->arr[i]) {
            swap(&h->arr[i], &h->arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    } else if (value > h->arr[0]) {
        h->arr[0] = value;
        heapify(h, 0);
    }
}

int main() {
    int prices[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = sizeof(prices) / sizeof(prices[0]);
    int k = 5;

    Heap *h = createHeap(k);

    for (int i = 0; i < n; i++)
        insert(h, prices[i]);

    printf("Top %d expensive prices are: ", k);
    for (int i = 0; i < k; i++)
        printf("%d ", h->arr[i]);

    free(h->arr);
    free(h);

    return 0;
}