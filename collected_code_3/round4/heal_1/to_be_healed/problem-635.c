#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int count;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*) malloc(sizeof(MinHeap));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'minHeap' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    minHeap->arr = (int*) malloc(sizeof(int)*capacity);
    minHeap->count = 0;
    minHeap->capacity = capacity;
    return minHeap;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->count && minHeap->arr[left] < minHeap->arr[smallest])
        smallest = left;

    if (right < minHeap->count && minHeap->arr[right] < minHeap->arr[smallest])
        smallest = right;

    if (smallest != idx) {
        swap(&minHeap->arr[smallest], &minHeap->arr[idx]);
        heapify(minHeap, smallest);
    }
}

void insert(MinHeap* minHeap, int val) {
    if (minHeap->count == minHeap->capacity)
        return;

    minHeap->count++;
    int i = minHeap->count - 1;
    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*minHeap.arr + (long unsigned int)i * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    minHeap->arr[i] = val;

    while (i != 0 && minHeap->arr[(i - 1) / 2] > minHeap->arr[i]) {
        swap(&minHeap->arr[i], &minHeap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int removeMin(MinHeap* minHeap) {
    if (minHeap->count == 0)
        return -1;

    int root = minHeap->arr[0];

    minHeap->arr[0] = minHeap->arr[minHeap->count - 1];
    minHeap->count--;
    heapify(minHeap, 0);

    return root;
}

int main() {
    MinHeap* minHeap = createMinHeap(11);
    insert(minHeap, 3);
    insert(minHeap, 2);
    insert(minHeap, 15);
    insert(minHeap, 5);
    insert(minHeap, 4);
    insert(minHeap, 45);

    printf("%d ", removeMin(minHeap));
    printf("%d ", removeMin(minHeap));
    printf("%d ", removeMin(minHeap));
    printf("%d ", removeMin(minHeap));
    printf("%d ", removeMin(minHeap));

    return 0;
}