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

void insertNode(Node** head, int data) {
    if (*head == NULL) {
        *head = createNode(data);
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = createNode(data);
}

void packDuplicates(Node* head) {
    while (head != NULL && head->next != NULL) {
        if (head->data == head->next->data) {
            printf("[%d, ", head->data);
            while (head->next != NULL && head->data == head->next->data) {
                printf("%d, ", head->next->data);
                head = head->next;
            }
            printf("\b\b], ");
        } else {
            printf("[%d], ", head->data);
        }
        head = head->next;
    }
    if (head != NULL) {
        printf("[%d]", head->data);
    }
}

int main() {
    Node* head = NULL;
    insertNode(&head, 1);
    insertNode(&head, 1);
    insertNode(&head, 2);
    insertNode(&head, 3);
    insertNode(&head, 3);
    insertNode(&head, 3);
    insertNode(&head, 4);
    insertNode(&head, 5);
    insertNode(&head, 5);
    packDuplicates(head);
    return 0;
}