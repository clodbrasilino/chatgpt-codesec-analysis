#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int getLength(struct Node* head) {
    int length = 0;
    struct Node* current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

struct Node* rotateLeft(struct Node* head, int k) {
    if (head == NULL || head->next == NULL || k <= 0) {
        return head;
    }
    
    int length = getLength(head);
    k = k % length;
    
    if (k == 0) {
        return head;
    }
    
    struct Node* current = head;
    int count = 1;
    
    while (count < k && current != NULL) {
        current = current->next;
        count++;
    }
    
    if (current == NULL) {
        return head;
    }
    
    struct Node* kthNode = current;
    
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = head;
    head = kthNode->next;
    kthNode->next = NULL;
    
    return head;
}

int main() {
    struct Node* head = NULL;
    
    appendNode(&head, 1);
    appendNode(&head, 2);
    appendNode(&head, 3);
    appendNode(&head, 4);
    appendNode(&head, 5);
    
    printf("Original list: ");
    printList(head);
    
    int k = 2;
    head = rotateLeft(head, k);
    
    printf("List after rotating left by %d: ", k);
    printList(head);
    
    freeList(head);
    
    return 0;
}