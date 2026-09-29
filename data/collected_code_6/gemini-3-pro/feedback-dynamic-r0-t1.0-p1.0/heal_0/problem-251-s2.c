#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* insertBeforeEach(struct Node* head, int value) {
    if (head == NULL) {
        return NULL;
    }

    struct Node* current = head;
    struct Node* newHead = NULL;
    struct Node* prev = NULL;

    while (current != NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            current = newHead;
            while (current != NULL) {
                struct Node* temp = current;
                current = current->next;
                free(temp);
            }
            return NULL;
        }

        newNode->data = value;
        newNode->next = current;

        if (prev == NULL) {
            newHead = newNode;
        } else {
            prev->next = newNode;
        }

        prev = current;
        current = current->next;
    }

    return newHead;
}

void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    if (head == NULL) {
        return 1;
    }
    head->data = 1;
    
    head->next = (struct Node*)malloc(sizeof(struct Node));
    if (head->next == NULL) {
        free(head);
        return 1;
    }
    head->next->data = 2;
    head->next->next = NULL;

    printList(head);

    head = insertBeforeEach(head, 0);
    if (head == NULL) {
        return 1;
    }

    printList(head);

    freeList(head);

    return 0;
}