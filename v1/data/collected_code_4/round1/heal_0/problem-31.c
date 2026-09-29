#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key, freq;
} Node;

typedef struct Heap {
    Node **array;
    int capacity, size;
} Heap;

Heap* createHeap(int capacity) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->capacity = capacity;
    h->size = 0;
    h->array = (Node**)malloc(h->capacity * sizeof(Node*));
    return h;
}

Node* createNode(int key, int freq) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->key = key;
    n->freq = freq;
    return n;
}

void swapNodes(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap* h, int idx) {
    int smallest = idx;
    int left = (idx << 1) + 1;
    int right = (idx + 1) << 1;

    if (left < h->size && h->array[left]->freq < h->array[smallest]->freq)
        smallest = left;

    if (right < h->size && h->array[right]->freq < h->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNodes(&(h->array[smallest]), &(h->array[idx]));
        heapify(h, smallest);
    }
}

void insertHeap(Heap* h, Node* n) {
    h->size++;
    int i = h->size - 1;
    while (i && n->freq < h->array[(i - 1)/2]->freq) {
        h->array[i] = h->array[(i - 1)/2];
        i = (i - 1)/2;
    }
    h->array[i] = n;
}

Node* extractMin(Heap* h) {
    Node* temp = h->array[0];
    h->array[0] = h->array[h->size - 1];
    --h->size;
    heapify(h, 0);
    return temp;
}

void findKTop(int *array, int n, int k) {
    Heap* h = createHeap(k);
    for(int i = 0; i < n; i++) {
        if(i < k) {
            h->array[i] = createNode(array[i], array[i]);
            if(i == k - 1)
                heapify(h, i);
        } else {
            if(array[i] > h->array[0]->freq) {
                h->array[0]->key = array[i];
                h->array[0]->freq = array[i];
                heapify(h, 0);
            }
        }
    }

    printf("Top %d numbers are: \n", k);
    while(h->size) {
        Node* n = extractMin(h);
        printf("%d ", n->key);
        free(n);
    }
    free(h->array);
    free(h);
}

int main() {
    int arr[] = {3, 1, 4, 4, 5, 2, 6, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    findKTop(arr, n, k);
    return 0;
}