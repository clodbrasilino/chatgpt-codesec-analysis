#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* removeOdd(Node* head) {
    Node* prev = NULL;
    Node* node = head;
    Node* next = NULL;
    
    while (node != NULL) {
        if (node->data % 2 != 0) {
            if (prev == NULL) {
                head = node->next;
            } else {
                prev->next = node->next;
            }
            next = node->next;
            free(node);
            node = next;
        } else {
            prev = node;
            node = node->next;
        }
    }
    return head;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(0);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
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

    printf("Original List: ");
    printList(head);

    head = removeOdd(head);

    printf("List after removing odd numbers: ");
    printList(head);

    return 0;
}