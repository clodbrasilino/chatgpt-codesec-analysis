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

    unsigned long long result = 1;
    struct Node* current = head;

    while (current != NULL) {
        result *= (unsigned long long)(long long)(current->data);
        current = current->next;
    }

    return (long long)result;
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
    int val;
    struct Node* head = NULL;
    struct Node* tail = NULL;

    while (scanf("%d", &val) == 1) {
        struct Node* newNode = createNode(val);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    long long product = multiplyListItems(head);
    
    if (head != NULL) {
        printf("%lld\n", product);
    }

    freeList(head);

    return 0;
}