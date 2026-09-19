#include <stdio.h>
#include <stdlib.h>

struct Node {
    long long data;
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

struct Node* createNode(long long data) {
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
    long long val;
    struct Node* head = NULL;
    struct Node* tail = NULL;

    while (scanf("%lld", &val) == 1) {
        struct Node* newNode = createNode(val);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    if (head != NULL) {
        long long product = multiplyListItems(head);
        printf("%lld\n", product);
    } else {
        printf("0\n");
    }

    freeList(head);

    return 0;
}