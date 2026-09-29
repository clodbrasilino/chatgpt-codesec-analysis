#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    if (!head) {
        return;
    }
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

Node* addLists(Node* list1, Node* list2) {
    Node* result = NULL;
    Node* current1 = list1;
    Node* current2 = list2;

    while (current1 && current2) {
        appendNode(&result, current1->data + current2->data);
        current1 = current1->next;
        current2 = current2->next;
    }

    while (current1) {
        appendNode(&result, current1->data);
        current1 = current1->next;
    }

    while (current2) {
        appendNode(&result, current2->data);
        current2 = current2->next;
    }

    return result;
}

void freeList(Node* head) {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void printList(Node* head) {
    Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* result = NULL;

    appendNode(&list1, 1);
    appendNode(&list1, 2);
    appendNode(&list1, 3);

    appendNode(&list2, 4);
    appendNode(&list2, 5);
    appendNode(&list2, 6);
    appendNode(&list2, 7);

    result = addLists(list1, list2);

    printList(result);

    freeList(list1);
    freeList(list2);
    freeList(result);

    return EXIT_SUCCESS;
}