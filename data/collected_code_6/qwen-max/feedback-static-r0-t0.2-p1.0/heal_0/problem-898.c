#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

Node* extractElements(Node* head, int count) {
    if (head == NULL || count <= 0) {
        return NULL;
    }

    Node* newHead = NULL;
    Node** currentPtr = &newHead;
    Node* current = head;

    while (count > 0 && current != NULL) {
        *currentPtr = createNode(current->data);
        if (*currentPtr == NULL) {
            freeList(newHead);
            return NULL;
        }
        currentPtr = &((*currentPtr)->next);
        current = current->next;
        count--;
    }

    return newHead;
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);

    int count = 3;
    Node* extracted = extractElements(head, count);

    Node* current = extracted;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    freeList(head);
    freeList(extracted);

    return 0;
}