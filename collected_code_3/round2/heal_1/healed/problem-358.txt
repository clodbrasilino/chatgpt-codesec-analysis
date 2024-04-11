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

void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (!newNode) return;
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void moduloDivision(Node* head1, Node* head2) {
    Node* temp1 = head1;
    Node* temp2 = head2;
    while (temp1 != NULL && temp2 != NULL) {
        printf("%d ", temp1->data % temp2->data);
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
}

void freeList(Node** head) {
    Node* current = *head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    *head = NULL;
}

int main() {
    Node* head1 = NULL;
    Node* head2 = NULL;

    insertEnd(&head1, 10);
    insertEnd(&head1, 20);
    insertEnd(&head1, 30);
    insertEnd(&head1, 40);

    insertEnd(&head2, 2);
    insertEnd(&head2, 3);
    insertEnd(&head2, 4);
    insertEnd(&head2, 5);

    moduloDivision(head1, head2);

    freeList(&head1);
    freeList(&head2);

    return 0;
}