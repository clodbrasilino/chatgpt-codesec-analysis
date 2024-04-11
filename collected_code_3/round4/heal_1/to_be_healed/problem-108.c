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
    HeapNode** heap = malloc(listsSize * sizeof(HeapNode*));
    for (int i = 0; i < listsSize; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'heap' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        heap[i] = malloc(sizeof(HeapNode));
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*heap_49 + _11' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
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
        if (!heap[0]->node)
            heap[0] = heap[--listsSize];

        heapify(heap, 0, listsSize);
    }

    free(heap);

    return head;
}

int main() {
    int listsSize = 3;
    Node** lists = malloc(listsSize * sizeof(Node*));

    for (int i = 0; i < listsSize; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'lists' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        lists[i] = malloc(sizeof(Node));
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*lists_46 + _8' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        lists[i]->val = i;
        lists[i]->next = malloc(sizeof(Node));
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '**_18.next' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
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