#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
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

Node* rotateRight(Node *head, int k) {
    if (head == NULL || head->next == NULL || k <= 0) return head;

    Node *current = head;
    int count = 1;
    while (current->next != NULL && ++count) {
        current = current->next;
    }

    current->next = head;
    k = k % count;
    k = count - k;
    while (k--) current = current->next;

    head = current->next;
    current->next = NULL;

    return head;
}

int main() {
    Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    int k = 2;
    head = rotateRight(head, k);

    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }

    freeList(head);
    return 0;
}