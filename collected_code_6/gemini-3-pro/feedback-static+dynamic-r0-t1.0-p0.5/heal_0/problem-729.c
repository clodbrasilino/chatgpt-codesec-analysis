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
    if (!head) return;
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

Node* addLists(Node* list1, Node* list2) {
    Node* result = NULL;
    Node* temp1 = list1;
    Node* temp2 = list2;

    while (temp1 && temp2) {
        appendNode(&result, temp1->data + temp2->data);
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    while (temp1) {
        appendNode(&result, temp1->data);
        temp1 = temp1->next;
    }

    while (temp2) {
        appendNode(&result, temp2->data);
        temp2 = temp2->next;
    }

    return result;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
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