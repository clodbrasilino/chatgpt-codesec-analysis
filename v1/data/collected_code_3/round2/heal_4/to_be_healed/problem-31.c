#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num;
    int freq;
} Node;

typedef struct {
    Node* heap;
    int size;
} Heap;

void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap* h, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    /* Possible weaknesses found:
     *  use of uninitialized value '*_4 + _6.freq' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    if (left < h->size && h->heap[left].freq < h->heap[smallest].freq)
        smallest = left;

    if (right < h->size && h->heap[right].freq < h->heap[smallest].freq)
        smallest = right;

    if (smallest != i) {
        swap(&h->heap[i], &h->heap[smallest]);
        heapify(h, smallest);
    }
}

void insert(Heap* h, Node node) {
    if(h->heap != NULL){
        ++h->size;
        int i = h->size - 1;
        while (i && node.freq < h->heap[(i - 1) / 2].freq) {
            h->heap[i] = h->heap[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        h->heap[i] = node;
    }
}

Node pop(Heap* h) {
    Node root = h->heap[0];
    if (h->size > 1) {
        h->heap[0] = h->heap[h->size - 1];
        --h->size;
        heapify(h, 0);
    } else {
        --h->size;
    }
    return root;
}

void topKFrequent(int* nums, int numsSize, int k) {
    int freq[100] = {0};
    for (int i = 0; i < numsSize; ++i)
        ++freq[nums[i] + 50];

    Heap* h = (Heap*)malloc(sizeof(Heap));
    if(h != NULL){
        h->heap = (Node*)malloc(sizeof(Node) * k);
        if(h->heap != NULL){
            h->size = 0;
            for (int i = 0; i < 100; ++i) {
                Node node = {i - 50, freq[i]};
                if (h->size < k) {
                    insert(h, node);
                } else if (h->heap[0].freq < node.freq) {
                    pop(h);
                    insert(h, node);
                }
            }

            while (h->size) {
                Node node = pop(h);
                printf("%d ", node.num);
            }
            free(h->heap);
            free(h);
        }
    }
}

int main() {
    int nums[] = {1, 1, 1, 2, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 2;
    topKFrequent(nums, numsSize, k);
    return 0;
}