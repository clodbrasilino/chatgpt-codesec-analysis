#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node* next;
} Node;

typedef struct HeapNode {
    Node* node;
    int listIndex;
} HeapNode;

void swap(HeapNode** a, HeapNode** b) {
    HeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(HeapNode** heap, int i, int heapSize) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && heap[left]->node->val < heap[smallest]->node->val)
        smallest = left;

    if (right < heapSize && heap[right]->node->val < heap[smallest]->node->val)
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify(heap, smallest, heapSize);
    }
}

Node* mergeSortedLists(Node** lists, int listsSize) {
    if (!lists) return NULL;

    HeapNode** heap = malloc(listsSize * sizeof(HeapNode*));
    if (!heap) return NULL;

    for (int i = 0; i < listsSize; i++) {
        heap[i] = malloc(sizeof(HeapNode));
        
        if (!heap[i]) return NULL;
        
        heap[i]->node = lists[i];
        heap[i]->listIndex = i;
    }

    for (int i = listsSize / 2 - 1; i >= 0; i--)
        heapify(heap, i, listsSize);

    Node* head = NULL;
    Node* last = NULL;

    while (heap[0]->node) {
        Node* node = heap[0]->node;

        if (!head) {
            head = node;
            last = node;
        } else {
            last->next = node;
            last = node;
        }

        heap[0]->node = heap[0]->node->next;
        if (!heap[0]->node && listsSize > 0)
            heap[0] = heap[--listsSize];

        heapify(heap, 0, listsSize);
    }

    free(heap);

    return head;
}

int main() {
    int listsSize = 3;
    Node** lists = malloc(listsSize * sizeof(Node*));

    if(!lists) return -1;

    for (int i = 0; i < listsSize; i++) {
        lists[i] = malloc(sizeof(Node));
        if(!lists[i]) return -1;
        lists[i]->val = i;
        lists[i]->next = malloc(sizeof(Node));
        if (!lists[i]->next) return -1;
        lists[i]->next->val = i + listsSize;
        lists[i]->next->next = NULL;
    }

    Node* merged = mergeSortedLists(lists, listsSize);

    while (merged) {
        printf("%d ", merged->val);
        merged = merged->next;
    }

    printf("\n");

    for (int i = 0; i < listsSize; i++) {
        free(lists[i]->next);
        free(lists[i]);
    }

    free(lists);

    return 0;
}