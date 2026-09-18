#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data);
int appendNode(Node** head_ref, int data);
void rotateLeft(Node** head_ref, size_t k);
void printList(const Node* head);
void freeList(Node** head_ref);

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

int appendNode(Node** head_ref, int data) {
    if (head_ref == NULL) {
        return 0;
    }
    
    Node* newNode = createNode(data);
    if (newNode == NULL) {
        return 0;
    }
    
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return 1;
    }
    
    Node* last = *head_ref;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
    
    return 1;
}

void rotateLeft(Node** head_ref, size_t k) {
    if (head_ref == NULL || *head_ref == NULL || k == 0) {
        return;
    }

    size_t length = 1;
    Node* tail = *head_ref;
    while (tail->next != NULL) {
        tail = tail->next;
        length++;
    }

    k = k % length;
    if (k == 0) {
        return;
    }

    Node* current = *head_ref;
    for (size_t i = 1; i < k; i++) {
        current = current->next;
    }

    Node* new_head = current->next;
    current->next = NULL;
    tail->next = *head_ref;
    *head_ref = new_head;
}

void printList(const Node* head) {
    const Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeList(Node** head_ref) {
    if (head_ref == NULL) {
        return;
    }
    
    Node* current = *head_ref;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
}

int main(void) {
    Node* head = NULL;
    int initial_values[] = {10, 20, 30, 40, 50, 60};
    size_t num_values = sizeof(initial_values) / sizeof(initial_values[0]);
    size_t rotation_amount = 4;

    for (size_t i = 0; i < num_values; i++) {
        if (!appendNode(&head, initial_values[i])) {
            freeList(&head);
            return EXIT_FAILURE;
        }
    }

    rotateLeft(&head, rotation_amount);
    printList(head);
    freeList(&head);

    return EXIT_SUCCESS;
}