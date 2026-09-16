#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

bool areElementsSame(Node* head) {
    if (head == NULL) {
        return true;
    }

    int firstValue = head->data;
    Node* current = head->next;

    while (current != NULL) {
        if (current->data != firstValue) {
            return false;
        }
        current = current->next;
    }

    return true;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
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
    Node* head1 = createNode(5);
    head1->next = createNode(5);
    head1->next->next = createNode(5);

    if (areElementsSame(head1)) {
        printf("List 1 elements are the same.\n");
    } else {
        printf("List 1 elements are not the same.\n");
    }

    Node* head2 = createNode(1);
    head2->next = createNode(2);
    head2->next->next = createNode(1);

    if (areElementsSame(head2)) {
        printf("List 2 elements are the same.\n");
    } else {
        printf("List 2 elements are not the same.\n");
    }

    freeList(head1);
    freeList(head2);

    return EXIT_SUCCESS;
}