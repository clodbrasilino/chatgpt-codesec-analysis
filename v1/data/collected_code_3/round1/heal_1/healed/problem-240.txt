#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(Node** head_ref, int new_data) {
    Node* new_node = createNode(new_data);
    if(new_node == NULL) {
        return;
    }
    Node* last = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
}

void replaceLastWithList(Node** head_ref, Node* new_list) {
    if (*head_ref == NULL || new_list == NULL)
        return;

    Node* temp = *head_ref;

    while (temp->next != NULL && temp->next->next != NULL)
        temp = temp->next;

    if(temp->next != NULL) {
        free(temp->next);
    }
    
    temp->next = new_list;
}

void printList(Node* node) {
    while (node != NULL) {
        printf(" %d ", node->data);
        node = node->next;
    }
}

int main() {
    Node* head = NULL;
    Node* new_list = NULL;

    append(&head, 1);
    append(&head, 2);
    append(&head, 3);

    append(&new_list, 4);
    append(&new_list, 5);
    append(&new_list, 6);

    replaceLastWithList(&head, new_list);

    printList(head);

    return 0;
}