#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, int data) {
    if (!head) return;
    
    Node* newNode = createNode(data);
    if (!*head) {
        *head = newNode;
        return;
    }
    
    Node* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void freeList(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

Node* rotateLeft(Node* head, int k) {
    if (!head || k <= 0) return head;
    
    Node* current = head;
    int count = 1;
    
    while (count < k && current != NULL) {
        current = current->next;
        count++;
    }
    
    if (current == NULL || current->next == NULL) {
        return head;
    }
    
    Node* kthNode = current;
    
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = head;
    head = kthNode->next;
    kthNode->next = NULL;
    
    return head;
}

int main(void) {
    Node* head = NULL;
    
    append(&head, 10);
    append(&head, 20);
    append(&head, 30);
    append(&head, 40);
    append(&head, 50);
    append(&head, 60);

    head = rotateLeft(head, 4);

    printList(head);

    freeList(head);
    
    return 0;
}