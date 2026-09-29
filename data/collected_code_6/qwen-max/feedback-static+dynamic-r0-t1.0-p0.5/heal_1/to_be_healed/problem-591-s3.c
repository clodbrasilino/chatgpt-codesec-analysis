#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void swapFirstLast(Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    Node* first = *head;
    Node* last = *head;
    Node* prev = NULL;

    /* Possible weaknesses found:
     *  Assuming that condition 'last->next!=NULL' is not redundant
     */
    while (last->next != NULL) {
        prev = last;
        last = last->next;
    }

    if (prev) {
        prev->next = first;
        /* Possible weaknesses found:
         *  Assignment 'first->next=last->next', assigned value is 0
         */
        first->next = last->next;
        /* Possible weaknesses found:
         *  Condition 'first->next' is always false
         *  Condition 'first->next' is always false [knownConditionTrueFalse]
         */
        last->next = first->next ? first->next : NULL;
        *head = last;
    }
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);

    printf("Original list: ");
    for (Node* current = head; current != NULL; current = current->next) {
        printf("%d ", current->data);
    }
    printf("\n");

    swapFirstLast(&head);

    printf("Modified list: ");
    for (Node* current = head; current != NULL; current = current->next) {
        printf("%d ", current->data);
    }
    printf("\n");

    freeList(head);
    return 0;
}