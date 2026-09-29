#include <stdio.h>
#include <stdlib.h>

// Define the Node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to shift first element to the end
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

// Function to add a node at the end of a list
void addToEnd(Node** head, int new_data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'new_node' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
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

// Function to print the list
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