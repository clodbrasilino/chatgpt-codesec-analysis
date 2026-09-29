#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int findMaxLengthSublist(Node *head, Node **maxHead, int *maxLen) {
    if (head == NULL) {
        return 0;
    }

    Node *current = head;
    Node *sublistStart = head;
    int currentLen = 1;
    int maxLength = 1;

    while (current->next != NULL) {
        if (current->data < current->next->data) {
            currentLen++;
        } else {
            if (currentLen > maxLength) {
                maxLength = currentLen;
                *maxHead = sublistStart;
                *maxLen = maxLength;
            }
            sublistStart = current->next;
            currentLen = 1;
        }
        current = current->next;
    }

    if (currentLen > maxLength) {
        maxLength = currentLen;
        *maxHead = sublistStart;
        *maxLen = maxLength;
    }

    return maxLength;
}

int main() {
    Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);
    head->next->next->next->next->next = createNode(6);

    Node *maxHead = NULL;
    int maxLen = 0;

    findMaxLengthSublist(head, &maxHead, &maxLen);

    printf("Max Length: %d\n", maxLen);
    Node *current = maxHead;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    freeList(head);
    return 0;
}