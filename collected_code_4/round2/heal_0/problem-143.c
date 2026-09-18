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
    linkedList->head = NULL;
    return linkedList;
}

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
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
        tuple[i] = newLinkedList();
        addToLinkedList(tuple[i], i);
    }
    printf("Number of lists in tuple: %d\n", numListsInTuple(tuple, numLists));
    for(i = 0; i < numLists; ++i) {
        free(tuple[i]);
    }
    free(tuple);
    return 0;
}