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
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void findMaxSublist(Node* head, Node** maxSublistHead, int* maxLength) {
    if (!head || !maxSublistHead || !maxLength) {
        return;
    }

    *maxSublistHead = NULL;
    *maxLength = 0;

    Node* current = head;
    Node* currentSublistHead = head;
    int currentLength = 1;

    while (current->next != NULL) {
        if (current->data < current->next->data) {
            currentLength++;
        } else {
            if (currentLength > *maxLength) {
                *maxLength = currentLength;
                *maxSublistHead = currentSublistHead;
            }
            currentSublistHead = current->next;
            currentLength = 1;
        }
        current = current->next;
    }

    if (currentLength > *maxLength) {
        *maxLength = currentLength;
        *maxSublistHead = currentSublistHead;
    }
}

void printSublist(Node* head, int length) {
    if (!head) {
        return;
    }
    Node* current = head;
    for (int i = 0; i < length && current != NULL; i++) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(5);
    head->next->next->next = createNode(3);
    head->next->next->next->next = createNode(4);
    head->next->next->next->next->next = createNode(6);
    head->next->next->next->next->next->next = createNode(7);
    head->next->next->next->next->next->next->next = createNode(2);

    Node* maxSublistHead = NULL;
    int maxLength = 0;

    findMaxSublist(head, &maxSublistHead, &maxLength);

    if (maxSublistHead) {
        printSublist(maxSublistHead, maxLength);
    }

    freeList(head);

    return 0;
}