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
    if (!linkedList) {
        return NULL;
    }
    linkedList->head = NULL;
    return linkedList;
}

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void addToLinkedList(LinkedList* linkedList, int data) {
    if (!linkedList) {
        return;
    }
    Node* node = newNode(data);
    if (!node) {
        return;
    }
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
    if (!tuple) {
        return -1;
    }
    for(i = 0; i < numLists; ++i) {
        tuple[i] = newLinkedList();
        if (!tuple[i]) {
            return -1;
        }
        addToLinkedList(tuple[i], i);
    }
    printf("Number of lists in tuple: %d\n", numListsInTuple(tuple, numLists));
    for(i = 0; i < numLists; ++i) {
        Node *node, *tmp;   
        node = tuple[i]->head; 
        while (node != NULL) {
            tmp = node;
            node = node->next;
            free(tmp);
        }
        free(tuple[i]);
    }
    free(tuple);
    return 0;
}