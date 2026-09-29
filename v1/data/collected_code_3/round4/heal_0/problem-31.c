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
    if (h->size == 0) {
        h->heap[0] = node;
        h->size++;
    } else {
        if (h->heap[0].freq < node.freq) {
            h->heap[0] = node;
            heapify(h, 0);
        }
    }
}

void topKFrequent(int* nums, int numsSize, int k) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->heap = (Node*)malloc(sizeof(Node) * k);
    h->size = 0;

    for (int i = 0; i < numsSize; i++) {
        Node node;
        node.num = nums[i];
        node.freq = 1;

        for (int j = i + 1; j < numsSize; j++) {
            if (nums[j] == nums[i]) {
                node.freq++;
                i++;
            } else {
                break;
            }
        }

        insert(h, node);
    }

    for (int i = 0; i < k; i++) {
        printf("%d ", h->heap[i].num);
    }

    free(h->heap);
    free(h);
}

int main() {
    int nums[] = {1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 5, 5, 5};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 3;

    topKFrequent(nums, numsSize, k);

    return 0;
}