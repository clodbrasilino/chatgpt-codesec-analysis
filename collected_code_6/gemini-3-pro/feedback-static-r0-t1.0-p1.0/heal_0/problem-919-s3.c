#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

long long multiplyListItems(struct Node* head) {
    if (head == NULL) {
        return 0; 
    }

    long long result = 1;
    struct Node* current = head;

    while (current != NULL) {
        result *= current->data;
        current = current->next;
    }

    return result;
}

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(struct Node* head) {
    struct Node* current = head;
    struct Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

int main(void) {
    struct Node* head = createNode(2);
    head->next = createNode(3);
    head->next->next = createNode(4);
    head->next->next->next = createNode(5);

    long long product = multiplyListItems(head);

    printf("Product of all items: %lld\n", product);

    freeList(head);

    return 0;
}