#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if(*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    /* Possible weaknesses found:
     *  leak of 'newNode' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    temp->next = newNode;
}

void moduloDivision(Node* head1, Node* head2) {
    Node* temp1 = head1;
    Node* temp2 = head2;
    while(temp1 != NULL && temp2 != NULL) {
        printf("%d ", temp1->data % temp2->data);
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
}

int main() {
    Node* head1 = NULL;
    Node* head2 = NULL;
    insertNode(&head1, 10);
    insertNode(&head1, 20);
    insertNode(&head1, 30);
    insertNode(&head2, 3);
    insertNode(&head2, 4);
    insertNode(&head2, 5);
    moduloDivision(head1, head2);
    return 0;
}