#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data);
void freeList(struct Node* head);
int recursiveSum(const struct Node* head);

int recursiveSum(const struct Node* head) {
    if (head == NULL) {
        return 0;
    }
    return head->data + recursiveSum(head->next);
}

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

void freeList(struct Node* head) {
    struct Node* current = head;
    struct Node* nextNode = NULL;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

int main(void) {
    struct Node* head = createNode(5);
    head->next = createNode(10);
    head->next->next = createNode(15);
    head->next->next->next = createNode(20);

    int totalSum = recursiveSum(head);
    
    printf("Sum of the list: %d\n", totalSum);

    freeList(head);

    return EXIT_SUCCESS;
}