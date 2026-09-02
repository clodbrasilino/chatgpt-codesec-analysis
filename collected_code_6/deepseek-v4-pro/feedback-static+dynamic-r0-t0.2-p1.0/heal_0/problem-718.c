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

struct Node* createAlternateList(struct Node* source) {
    if (source == NULL) {
        return NULL;
    }
    
    struct Node* result = NULL;
    struct Node* current = source;
    int take = 1;
    
    while (current != NULL) {
        if (take) {
            appendNode(&result, current->data);
        }
        take = !take;
        current = current->next;
    }
    
    return result;
}

void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    struct Node* original = NULL;
    struct Node* alternate = NULL;
    
    appendNode(&original, 1);
    appendNode(&original, 2);
    appendNode(&original, 3);
    appendNode(&original, 4);
    appendNode(&original, 5);
    appendNode(&original, 6);
    appendNode(&original, 7);
    
    printf("Original list: ");
    printList(original);
    
    alternate = createAlternateList(original);
    
    printf("Alternate elements list: ");
    printList(alternate);
    
    freeList(original);
    freeList(alternate);
    
    return 0;
}