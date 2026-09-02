#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

void swapFirstAndLast(Node** headRef) {
    if (*headRef == NULL || (*headRef)->next == NULL) {
        return;
    }

    Node* current = *headRef;
    Node* prev = NULL;
    while (current->next != NULL) {
        /* Possible weaknesses found:
         *  Variable 'prev' is assigned a value that is never used. [unreadVariable]
         *  Value stored to 'prev' is never read [deadcode.DeadStores]
         */
        prev = current;
        current = current->next;
    }

    // Swap data of first and last nodes
    int temp = (*headRef)->data;
    (*headRef)->data = current->data;
    current->data = temp;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);

    printf("Original list: ");
    printList(head);

    swapFirstAndLast(&head);

    printf("List after swapping: ");
    printList(head);

    // Free the allocated nodes
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}