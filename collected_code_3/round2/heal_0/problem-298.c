#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) {
        printf("Error creating a new node.\n");
        exit(0);
    }
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void insertNode(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

int findElement(Node* head, int data) {
    Node* current = head;
    while(current != NULL) {
        if(current->data == data) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void findNestedElements(Node* head1, Node* head2) {
    Node* current = head1;
    while(current != NULL) {
        if(findElement(head2, current->data)) {
            printf("%d ", current->data);
        }
        current = current->next;
    }
}

int main() {
    Node* head1 = NULL;
    Node* head2 = NULL;

    insertNode(&head1, 1);
    insertNode(&head1, 2);
    insertNode(&head1, 3);
    insertNode(&head1, 4);
    insertNode(&head1, 5);

    insertNode(&head2, 3);
    insertNode(&head2, 4);
    insertNode(&head2, 5);
    insertNode(&head2, 6);
    insertNode(&head2, 7);

    printf("Nested elements are: ");
    findNestedElements(head1, head2);

    return 0;
}