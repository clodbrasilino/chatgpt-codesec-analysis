#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(Node **head, int data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int countNodes(Node *head) {
    int count = 0;
    Node *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

Node* rotateRight(Node *head, int k) {
    if (head == NULL || head->next == NULL || k == 0) {
        return head;
    }

    int n = countNodes(head);
    k = k % n;
    if (k == 0) {
        return head;
    }

    Node *current = head;
    for (int i = 1; i < n - k; i++) {
        current = current->next;
    }

    Node *newHead = current->next;
    current->next = NULL;

    Node *temp = newHead;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = head;

    return newHead;
}

int main() {
    Node *head = NULL;
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 4);
    insertAtEnd(&head, 5);

    printf("Original list: ");
    printList(head);

    int k = 2;
    head = rotateRight(head, k);

    printf("Rotated list by %d positions: ", k);
    printList(head);

    return 0;
}