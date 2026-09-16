#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node** head, int data) {
    Node* newNode = createNode(data);
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

void deleteKthNode(Node** head, int k) {
    if (k <= 0 || *head == NULL) return;

    Node* temp = *head;
    Node* prev = NULL;
    int count = 1;

    while (temp != NULL && count < k) {
        prev = temp;
        temp = temp->next;
        count++;
    }

    if (temp == NULL) return;

    if (prev == NULL) {
        *head = (*head)->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;

    insertNode(&head, 10);
    insertNode(&head, 20);
    insertNode(&head, 30);
    insertNode(&head, 40);
    insertNode(&head, 50);

    printf("Original list: ");
    printList(head);

    deleteKthNode(&head, 3);

    printf("List after deleting 3rd element: ");
    printList(head);

    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}