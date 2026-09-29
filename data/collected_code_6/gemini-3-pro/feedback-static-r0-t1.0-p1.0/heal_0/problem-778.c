#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Sublist {
    Node* head;
    struct Sublist* next;
} Sublist;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Sublist* createSublist(Node* head) {
    Sublist* newSublist = (Sublist*)malloc(sizeof(Sublist));
    if (!newSublist) {
        exit(EXIT_FAILURE);
    }
    newSublist->head = head;
    newSublist->next = NULL;
    return newSublist;
}

Sublist* packConsecutiveDuplicates(Node* head) {
    if (!head) {
        return NULL;
    }

    Sublist* resultHead = NULL;
    Sublist* resultTail = NULL;
    Node* current = head;

    while (current) {
        int currentData = current->data;
        Node* sublistHead = createNode(currentData);
        Node* sublistTail = sublistHead;

        current = current->next;
        while (current && current->data == currentData) {
            sublistTail->next = createNode(currentData);
            sublistTail = sublistTail->next;
            current = current->next;
        }

        Sublist* newSublist = createSublist(sublistHead);
        if (!resultHead) {
            resultHead = newSublist;
            resultTail = resultHead;
        } else {
            resultTail->next = newSublist;
            resultTail = resultTail->next;
        }
    }

    return resultHead;
}

void printAndFreeSublists(Sublist* head) {
    Sublist* currentSublist = head;
    while (currentSublist) {
        Sublist* nextSublist = currentSublist->next;
        Node* currentNode = currentSublist->head;
        
        printf("[");
        while (currentNode) {
            Node* nextNode = currentNode->next;
            printf("%d", currentNode->data);
            if (nextNode) {
                printf(", ");
            }
            free(currentNode);
            currentNode = nextNode;
        }
        printf("] ");
        
        free(currentSublist);
        currentSublist = nextSublist;
    }
    printf("\n");
}

void freeList(Node* head) {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node* head = createNode(1);
    head->next = createNode(1);
    head->next->next = createNode(2);
    head->next->next->next = createNode(3);
    head->next->next->next->next = createNode(3);
    head->next->next->next->next->next = createNode(3);
    head->next->next->next->next->next->next = createNode(4);

    Sublist* packed = packConsecutiveDuplicates(head);
    printAndFreeSublists(packed);

    freeList(head);

    return 0;
}