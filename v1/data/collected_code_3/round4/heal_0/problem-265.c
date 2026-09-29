#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void splitList(Node* head, int n, Node** first, Node** second) {
    Node* current = head;
    int count = 0;
    while (current != NULL && count < n) {
        count++;
        if (count == n) {
            *second = current->next;
            current->next = NULL;
            *first = head;
        }
        current = current->next;
    }
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    Node* first = NULL;
    Node* second = NULL;

    splitList(head, 3, &first, &second);

    printList(first);
    printList(second);

    return 0;
}