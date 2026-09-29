#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void replaceLastWithList(Node** head, Node* newList) {
    if (*head == NULL || newList == NULL) {
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL && temp->next->next != NULL) {
        temp = temp->next;
    }
    temp->next = newList;
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* list1 = NULL;
    appendNode(&list1, 1);
    appendNode(&list1, 2);
    appendNode(&list1, 3);

    Node* list2 = NULL;
    appendNode(&list2, 4);
    appendNode(&list2, 5);

    printf("Original List 1: ");
    printList(list1);

    printf("List to Append: ");
    printList(list2);

    replaceLastWithList(&list1, list2);

    printf("Modified List 1: ");
    printList(list1);

    return 0;
}