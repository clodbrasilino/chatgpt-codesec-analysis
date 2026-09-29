#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;

LinkedList* newLinkedList() {
    LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'linkedList' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    linkedList->head = NULL;
    return linkedList;
}

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    node->data = data;
    node->next = NULL;
    return node;
}

void addToLinkedList(LinkedList* linkedList, int data) {
    Node* node = newNode(data);
    node->next = linkedList->head;
    linkedList->head = node;
}

int numListsInTuple(LinkedList** tuple, int size) {
    return size;
}

int main() {
    int i;
    int numLists = 3;
    LinkedList** tuple = (LinkedList**)malloc(numLists * sizeof(LinkedList*));
    for(i = 0; i < numLists; ++i) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'tuple' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        tuple[i] = newLinkedList();
        addToLinkedList(tuple[i], i);
    }
    printf("Number of lists in tuple: %d\n", numListsInTuple(tuple, numLists));
    for(i = 0; i < numLists; ++i) {
        /* Possible weaknesses found:
         *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        free(tuple[i]);
    }
    free(tuple);
    return 0;
}