#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void shiftFirstToEnd(Node** head) {
    if (*head == NULL)
        return;
    
    Node* firstNode = *head;
    Node* temp = *head; 
  
    while (temp->next != NULL)
        temp = temp->next;
  
    temp->next = firstNode;
    *head = (*head)->next;
    firstNode->next = NULL;
}

void addToEnd(Node** head, int new_data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Allocation failed!\n");
        return;
    }
    new_node->data  = new_data;
    new_node->next = NULL;
    
    if (*head == NULL) {
        *head = new_node;
        return;
    }
  
    Node* last = *head;
    while (last->next != NULL)
        last = last->next;
  
    last->next = new_node;
    return;
}

void printList(Node* node) {
    while (node != NULL) {
        printf(" %d ", node->data);
        node = node->next;
    }
}

int main() {
    Node* head = NULL;

    addToEnd(&head, 1);
    addToEnd(&head, 2);
    addToEnd(&head, 3);
    addToEnd(&head, 4);
  
    shiftFirstToEnd(&head);
  
    printList(head);
  
    return 0;
}