#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

bool isSublist(Node *list, Node *sublist) {
    Node *ptr1 = list;
    while (ptr1 != NULL) {
        Node *ptr2 = sublist;
        Node *temp = ptr1;
        while (ptr2 != NULL && temp != NULL && ptr2->data == temp->data) {
            ptr2 = ptr2->next;
            temp = temp->next;
        }
        if (ptr2 == NULL) return true;
        ptr1 = ptr1->next;
    }
    return false;
}

int main() {
    Node *list = createNode(1);
    list->next = createNode(2);
    list->next->next = createNode(3);
    list->next->next->next = createNode(4);
    list->next->next->next->next = createNode(5);

    Node *sublist = createNode(2);
    sublist->next = createNode(3);
    sublist->next->next = createNode(4);

    if (isSublist(list, sublist)) {
        printf("Sublist found\n");
    } else {
        printf("Sublist not found\n");
    }

    // Clean up
    Node *current = list;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    current = sublist;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}