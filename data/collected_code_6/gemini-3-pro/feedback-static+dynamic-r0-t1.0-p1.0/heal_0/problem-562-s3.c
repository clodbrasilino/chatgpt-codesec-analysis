#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int maxSubListLength(struct Node* head) {
    if (head == NULL) {
        return 0;
    }

    int maxLength = 1;
    int currentLength = 1;
    struct Node* current = head;

    while (current->next != NULL) {
        if (current->data <= current->next->data) {
            currentLength++;
        } else {
            if (currentLength > maxLength) {
                maxLength = currentLength;
            }
            currentLength = 1;
        }
        current = current->next;
    }

    if (currentLength > maxLength) {
        maxLength = currentLength;
    }

    return maxLength;
}

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

void freeList(struct Node* head) {
    struct Node* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    struct Node* head = createNode(1);
    if (head == NULL) return 1;

    head->next = createNode(2);
    if (head->next == NULL) {
        freeList(head);
        return 1;
    }
    
    head->next->next = createNode(5);
    if (head->next->next == NULL) {
        freeList(head);
        return 1;
    }

    head->next->next->next = createNode(3);
    if (head->next->next->next == NULL) {
        freeList(head);
        return 1;
    }

    head->next->next->next->next = createNode(4);
    if (head->next->next->next->next == NULL) {
        freeList(head);
        return 1;
    }

    head->next->next->next->next->next = createNode(6);
    if (head->next->next->next->next->next == NULL) {
        freeList(head);
        return 1;
    }

    int result = maxSubListLength(head);
    printf("%d\n", result);

    freeList(head);

    return 0;
}