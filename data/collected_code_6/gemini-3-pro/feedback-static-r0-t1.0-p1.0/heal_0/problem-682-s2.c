#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head, int data) {
    if (!head) return;
    Node* newNode = createNode(data);
    if (!*head) {
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

Node* multiplyLists(Node* list1, Node* list2) {
    Node* result = NULL;
    Node* current1 = list1;
    Node* current2 = list2;

    while (current1 && current2) {
        append(&result, current1->data * current2->data);
        current1 = current1->next;
        current2 = current2->next;
    }

    return result;
}

void printList(Node* head) {
    Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    Node* current = head;
    Node* next = NULL;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* result = NULL;

    append(&list1, 2);
    append(&list1, 4);
    append(&list1, 6);

    append(&list2, 3);
    append(&list2, 5);
    append(&list2, 7);

    result = multiplyLists(list1, list2);

    printList(result);

    freeList(list1);
    freeList(list2);
    freeList(result);

    return 0;
}