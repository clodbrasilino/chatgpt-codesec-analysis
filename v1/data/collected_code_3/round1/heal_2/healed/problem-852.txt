#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* removeNegatives(Node* head) {
    Node* current = head;
    Node* prev = NULL;

    while (current != NULL) {
        if (current->data < 0) {
            Node* temp = current;
            current = current->next;

            if (prev == NULL) {
                head = current;
            } else {
                prev->next = current;
            }

            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }

    return head;
}

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));

    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->next = NULL;
    return node;
}

void printList(Node* head) {
    Node* current = head;

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }

    printf("\n");
}

int main() {
    Node* head = newNode(-10);
    Node* nextNode;

    if (head == NULL) {
        return 1;
    }

    nextNode = newNode(20);
    if(nextNode == NULL)
        return 1;
    head->next = nextNode;

    nextNode = newNode(-30);
    if(nextNode == NULL)
        return 1;
    head->next->next = nextNode;

    nextNode = newNode(40);
    if(nextNode == NULL)
        return 1;
    head->next->next->next = nextNode;

    nextNode = newNode(-50);
    if(nextNode == NULL)
        return 1;
    head->next->next->next->next = nextNode;

    printf("Original List: ");
    printList(head);

    head = removeNegatives(head);

    printf("List after removing negatives: ");
    printList(head);

    return 0;
}