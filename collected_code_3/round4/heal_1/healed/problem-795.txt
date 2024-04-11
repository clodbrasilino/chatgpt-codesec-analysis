#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int len;
    int capacity;
} Heap;

Heap* createHeap(int capacity) {
    Heap *h = (Heap*)malloc(sizeof(Heap));
    if (h == NULL) {
        return NULL;
    }
    h->data = (int*)malloc(sizeof(int) * capacity);
    if (h->data == NULL){
        free(h);
        return NULL;
    }
    h->len = 0;
    h->capacity = capacity;
    return h;
}

void pushHeap(Heap *h, int value) {
    if (h == NULL || h->data == NULL) {
        return;
    }
    if (h->len == h->capacity) {
        h->data[0] = value;
        for (int i = 0; i < h->len; ++i) {
            int child = 2 * i + 1;
            if (child + 1 < h->len && h->data[child] < h->data[child + 1]) {
                ++child;
            }
            if (h->data[i] < h->data[child]) {
                int temp = h->data[i];
                h->data[i] = h->data[child];
                h->data[child] = temp;
            } else {
                break;
            }
        }
    } else {
        h->data[h->len] = value;
        int i = h->len;
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (h->data[parent] < h->data[i]) {
                int temp = h->data[parent];
                h->data[parent] = h->data[i];
                h->data[i] = temp;
                i = parent;
            } else {
                break;
            }
        }
        ++h->len;
    }
}

int* getLeastNumbers(int* arr, int arrSize, int k, int* returnSize) {
    *returnSize = k;
    if (k == 0) {
        return NULL;
    }
    Heap *h = createHeap(k);
    if (h == NULL) {
        return NULL;
    }
    for (int i = 0; i < arrSize; ++i) {
        pushHeap(h, arr[i]);
    }
    int *result = (int*)malloc(sizeof(int) * k);
    if (result == NULL) {
        free(h->data);
        free(h);
        return NULL;
    }
    for (int i = 0; i < k; ++i) {
        result[i] = h->data[i];
    }
    free(h->data);
    free(h);
    return result;
}

int main() {
    int arr[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int returnSize;
    int *result = getLeastNumbers(arr, sizeof(arr) / sizeof(int), 4, &returnSize);
    if (result != NULL) {
        for (int i = 0; i < returnSize; ++i) {
            printf("%d ", result[i]);
        }
    }
    free(result);
    return 0;
}