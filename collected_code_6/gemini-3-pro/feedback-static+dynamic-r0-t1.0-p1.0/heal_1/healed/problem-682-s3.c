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
    Node* newNode = createNode(data);
    if (!*head) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void freeList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

Node* multiplyLists(Node* list1, Node* list2) {
    Node* result = NULL;
    Node* p1 = list1;
    Node* p2 = list2;

    while (p1 && p2) {
        append(&result, p1->data * p2->data);
        p1 = p1->next;
        p2 = p2->next;
    }

    return result;
}

void printList(Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(void) {
    Node* list1 = NULL;
    Node* list2 = NULL;

    append(&list1, 2);
    append(&list1, 4);
    append(&list1, 6);

    append(&list2, 3);
    append(&list2, 5);
    append(&list2, 7);

    Node* result = multiplyLists(list1, list2);

    printList(result);

    freeList(list1);
    freeList(list2);
    freeList(result);

    return 0;
}