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

void freeList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

Node* moduloLists(Node* list1, Node* list2) {
    Node* result = NULL;
    Node* temp1 = list1;
    Node* temp2 = list2;

    while (temp1 && temp2) {
        if (temp2->data == 0) {
            freeList(result);
            return NULL;
        }
        appendNode(&result, temp1->data % temp2->data);
        temp1 = temp1->next;
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

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;
    Node* result = NULL;

    appendNode(&list1, 10);
    appendNode(&list1, 20);
    appendNode(&list1, 30);

    appendNode(&list2, 3);
    appendNode(&list2, 7);
    appendNode(&list2, 4);

    result = moduloLists(list1, list2);

    if (result) {
        printList(result);
    } else {
        printf("Error: Division by zero encountered.\n");
    }

    freeList(list1);
    freeList(list2);
    freeList(result);

    return 0;
}