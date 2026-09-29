#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

Node* findMaxSublist(Node* head, int* maxLength) {
    if (!head) {
        *maxLength = 0;
        return NULL;
    }

    Node* current = head;
    Node* maxSublistStart = head;
    Node* currentSublistStart = head;
    
    int currentLength = 1;
    *maxLength = 1;

    while (current->next != NULL) {
        if (current->next->data > current->data) {
            currentLength++;
        } else {
            if (currentLength > *maxLength) {
                *maxLength = currentLength;
                maxSublistStart = currentSublistStart;
            }
            currentLength = 1;
            currentSublistStart = current->next;
        }
        current = current->next;
    }

    if (currentLength > *maxLength) {
        *maxLength = currentLength;
        maxSublistStart = currentSublistStart;
    }

    return maxSublistStart;
}

void printSublist(Node* start, int length) {
    Node* current = start;
    for (int i = 0; i < length && current != NULL; i++) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(5);
    head->next->next->next = createNode(3);
    head->next->next->next->next = createNode(4);
    head->next->next->next->next->next = createNode(6);
    head->next->next->next->next->next->next = createNode(7);
    head->next->next->next->next->next->next->next = createNode(2);

    int maxLength = 0;
    Node* maxSublist = findMaxSublist(head, &maxLength);

    if (maxSublist) {
        printSublist(maxSublist, maxLength);
    }

    freeList(head);
    return 0;
}