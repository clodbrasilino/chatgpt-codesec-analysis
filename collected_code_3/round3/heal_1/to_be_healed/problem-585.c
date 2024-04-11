#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int count;
    int size;
} Heap;

Heap *createHeap(int size) {
    Heap *h = (Heap *) malloc(sizeof(Heap));
    if(h == NULL) {
        return NULL;
    }
    h->count = 0;
    h->size = size;
    h->data = (int *) malloc(sizeof(int) * h->size);
    if(h->data == NULL) {
        return NULL;
    }
    return h;
}

void pushHeap(Heap *h, int value) {
    int i;
    /* Possible weaknesses found:
     *  dereference of NULL 'h' [CWE-476] [-Wanalyzer-null-dereference]
     */
    if(h->count == h->size)
        return;
    h->data[h->count] = value;
    i = h->count;
    while(i > 0 && h->data[i] > h->data[(i - 1) / 2]) {
        int temp = h->data[(i - 1) / 2];
        h->data[(i - 1) / 2] = h->data[i];
        h->data[i] = temp;
        i = (i - 1) / 2;
    }
    h->count++;
}

int popHeap(Heap *h) {
    int i, value;
    if(h->count == 0)
        return -1;
    value = h->data[0];
    h->count--;
    h->data[0] = h->data[h->count];
    i = 0;
    while((2 * i + 1) < h->count) {
        int maxIndex = 2 * i + 1;
        if((2 * i + 2) < h->count && h->data[2 * i + 2] > h->data[maxIndex])
            maxIndex = 2 * i + 2;
        if(h->data[i] >= h->data[maxIndex])
            break;
        int temp = h->data[i];
        h->data[i] = h->data[maxIndex];
        h->data[maxIndex] = temp;
        i = maxIndex;
    }
    return value;
}

void findNExpensiveItems(int *prices, int n, int size) {
    Heap *h = createHeap(n);
    int i;
    for(i = 0; i < n; i++)
        pushHeap(h, prices[i]);
    for(i = n; i < size; i++) {
        if(prices[i] > h->data[0]) {
            popHeap(h);
            pushHeap(h, prices[i]);
        }
    }
    for(i = 0; i < n; i++)
        printf("%d ", popHeap(h));
    printf("\n");
}

int main() {
    int prices[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int n = 5;
    findNExpensiveItems(prices, n, sizeof(prices) / sizeof(prices[0]));
    return 0;
}