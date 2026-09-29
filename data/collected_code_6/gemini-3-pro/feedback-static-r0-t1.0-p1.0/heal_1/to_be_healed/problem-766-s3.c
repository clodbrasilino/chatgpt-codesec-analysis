#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void iteratePairs(Node* head) {
    if (head == NULL) {
        return;
    }

    Node* current = head;
    while (current->next != NULL) {
        printf("(%d, %d)\n", current->data, current->next->data);
        current = current->next;
    }
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node* head) {
    /* Possible weaknesses found:
     *  The scope of the variable 'tmp' can be reduced. [variableScope]
     */
    Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    iteratePairs(head);

    freeList(head);

    return 0;
}