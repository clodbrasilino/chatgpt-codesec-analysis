#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data);
void appendNode(Node** head, int data);
Node* rotateLeft(Node* head, int k);
void printList(const Node* head);
void freeList(Node* head);

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    if (head == NULL) {
        return;
    }
    
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

Node* rotateLeft(Node* head, int k) {
    if (head == NULL || head->next == NULL || k <= 0) {
        return head;
    }

    int length = 1;
    Node* tail = head;
    while (tail->next != NULL) {
        length++;
        tail = tail->next;
    }

    k = k % length;
    if (k == 0) {
        return head;
    }

    Node* current = head;
    for (int i = 1; i < k; i++) {
        current = current->next;
    }

    Node* newHead = current->next;
    current->next = NULL;
    tail->next = head;

    return newHead;
}

void printList(const Node* head) {
    const Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    Node* head = NULL;

    appendNode(&head, 10);
    appendNode(&head, 20);
    appendNode(&head, 30);
    appendNode(&head, 40);
    appendNode(&head, 50);

    head = rotateLeft(head, 2);
    printList(head);

    head = rotateLeft(head, 8);
    printList(head);
    
    freeList(head);
    
    return EXIT_SUCCESS;
}